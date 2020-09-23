#pragma once

#include "ClientHandler.hpp"
#include "../solvers/Solver.hpp"
#include "../solvers/SearchSolver.hpp"
#include "../solvers/SolverFactory.hpp"
#include "../cachemanager/CacheManager.hpp"
#include "../cachemanager/SolverOperation.hpp"
#include "../exceptions/StatusException.hpp"
#include "../cachemanager/util/HashUtil.hpp"
#include <unistd.h>
#include <iostream>
#include <string>

namespace server {

    namespace clientside {

        template <typename Problem, typename Solution>
        class SolverClientHandler : public ClientHandler {

            static const uint32_t s_bufferSize = 1000000;
            static constexpr double s_version = 1.0;
            static const uint32_t s_emptyResponseLength = 0;
            static const uint32_t s_successStatus = 0;
            mutable cache::CacheManager m_cache;

            public:

                SolverClientHandler(const cache::CacheManager& cache)
                : m_cache(cache) {}

                void handleClient(const uint32_t clientSocket) const override {

                    // read problem
                    std::string command;
                    try {
                        command = readSock(clientSocket);
                    } catch (const status_exception::StatusException& e) {
                        
                        try {
                            writeSock(clientSocket, getLog(e.getStatus(), s_emptyResponseLength));
                        } catch (...) {}

                        close(clientSocket);
                        return;
                    }

                    // success in recieving problem
                    try {
                        writeSock(clientSocket, getLog(s_successStatus, s_emptyResponseLength));
                    } catch (...) {
                        close(clientSocket);
                        return;
                    }

                    // read input
                    std::string problemString;
                    try {
                        problemString = readSock(clientSocket);
                    } catch (const status_exception::StatusException& e) {
                        
                        try {
                            writeSock(clientSocket, getLog(e.getStatus(), s_emptyResponseLength));
                        } catch (...) {}

                        close(clientSocket);
                        return;
                    }

                    std::cout << command << std::endl;
                    std::cout << problemString << std::endl;

                    // success in recieving input, solving the problem with the input.
                    // this variable will hold the solution, as string
                    std::string solutionString;
                    // this variable will hold the status of the solving
                    uint32_t status = 0;

                    // first, searching for the solution in the cache:
                    // getting the hashCode of the operation
                    const uint32_t hashCode = util::HashUtil::calculateHash(command + problemString);
                    // if the operation result also exists in the cache, so getting it from the cache
                    if (m_cache.contains(hashCode)) {
                        try {
                            solutionString = m_cache.getOperationFileContent(hashCode);
                            // loading the operation into the cache
                            m_cache.load(operation::SolverOperation(hashCode, solutionString));
                        } catch (...) {
                            status = 6;
                        }

                    } else {
                        //getting the right solver according to the specific command
                        solver::SolverFactory<Problem, Solution> sFactory = solver::SolverFactory<Problem, Solution>();
                    
                        try {
                            const auto solver = sFactory.getSolver(command);
                            solutionString = solver->solve(problemString);
                            // loading the operation into the cache
                            m_cache.load(operation::SolverOperation(hashCode, solutionString));
                        }
                        catch(const status_exception::StatusException& e){
                            status = e.getStatus();
                        }
                        catch (...) {
                            status = 5;
                        }
                    }

                    // the calculation has succeeded
                    if (status == 0) {
                        // send success message
                        try {
                            writeSock(clientSocket, getLog(status, solutionString.size()));
                            writeSock(clientSocket, solutionString);
                        } catch (...) {
                            close(clientSocket);
                            return;
                        }
                    }
                    // if the calculation has failed
                    else {
                        // send error message
                        try {
                            writeSock(clientSocket, getLog(status, s_emptyResponseLength));
                        } catch (...) {
                            close(clientSocket);
                            return;
                        }
                    }

                    // close the port
                    close(clientSocket);          
                }

                void writeSock(const uint32_t clientSocket, std::string message) const {
                    if (write(clientSocket, message.c_str(), message.size()) < 0) {
                        throw status_exception::StatusException("Failed writing to socket", 7);
                    }
                }

                std::string readSock(const uint32_t clientSocket) const {
                    
                    char buffer[s_bufferSize];
                    size_t bytesRead;
                    int messageSize = 0;

                    while (bytesRead == read(clientSocket, buffer + messageSize, sizeof(buffer) - messageSize - 1) >= 0) {
                        messageSize += bytesRead;
                        if (messageSize > s_bufferSize - 1) {
                            throw status_exception::StatusException("Failed writing to socket", 6);
                        }
                        if(buffer[messageSize - 4] == '\r' && buffer[messageSize - 3] == '\n'
                         && buffer[messageSize - 2] == '\r' && buffer[messageSize - 1] == '\n'){
                            break;
                        }
                    }

                    if (bytesRead < 0) {
                        throw status_exception::StatusException("Failed writing to socket", 6);
                    }

                    std::string message = static_cast<std::string>(buffer);

                    return message.substr(0, message.size() - 4);
                }    
            
                std::string getLog(uint32_t status, uint32_t length) const {
                    return "Version: " + std::to_string(s_version) + "\r\n"
                    + "status: " + std::to_string(status) + "\r\n"
                    + "response-length: " + std::to_string(length) + "\r\n";
                }
        };
    }
}

