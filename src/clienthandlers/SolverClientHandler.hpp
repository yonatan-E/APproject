#pragma once

#include "AbstractClientHandler.hpp"
#include "../solvers/SolverFactory.hpp"
#include "../cachemanager/CacheManager.hpp"
#include "../cachemanager/SolverOperation.hpp"
#include "../exceptions/StatusException.hpp"
#include "../cachemanager/util/HashUtil.hpp"
#include <iostream>

namespace server_side {

    namespace client_handler {

        template <typename Problem, typename Solution>
        class SolverClientHandler : public AbstractClientHandler {

            static constexpr double s_VERSION = 1.0;
            static constexpr uint32_t s_SUCCESS_STATUS = 0;
            static constexpr uint32_t s_EMPTY_RESPONSE_LENGTH = 0;

            mutable cache::CacheManager m_cache;

            public:

                SolverClientHandler(const cache::CacheManager& cache)
                : m_cache(cache) {}

                void handleClient(const uint32_t clientSocket) const override {

                    // read problem
                    std::string commandString;
                    try {
                        commandString = readSock(clientSocket);
                        std::cerr << commandString << std::endl;
                    } catch (const status_exception::StatusException& e) {
                        
                        try {
                            writeSock(clientSocket, getLog(e.getStatus(), s_EMPTY_RESPONSE_LENGTH));
                        } catch (...) {}

                        try {
                            closeSock(clientSocket);
                        } catch (...) {}
                        
                        return;
                    }

                    // success in recieving problem
                    try {
                        writeSock(clientSocket, getLog(s_SUCCESS_STATUS, s_EMPTY_RESPONSE_LENGTH));
                    } catch (...) {

                        try {
                            closeSock(clientSocket);
                        } catch (...) {}

                        return;
                    }

                    // read input
                    std::string problemString;
                    try {
                        problemString = readSock(clientSocket);
                    } catch (const status_exception::StatusException& e) {
                        
                        try {
                            writeSock(clientSocket, getLog(e.getStatus(), s_EMPTY_RESPONSE_LENGTH));
                        } catch (...) {}

                        try {
                            closeSock(clientSocket);
                        } catch (...) {}

                        return;
                    }

                    // success in recieving input, solving the problem with the input.
                    // this variable will hold the solution, as string
                    std::string solutionString;
                    // this variable will hold the status of the solving
                    uint32_t status = 0;

                    // first, searching for the solution in the cache:
                    // getting the hashCode of the operation
                    const uint32_t hashCode = util::HashUtil::calculateHash(commandString + problemString);
                    // if the operation result also exists in the cache, so getting it from the cache
                    if (m_cache.contains(hashCode)) {
                        try {
                            solutionString = m_cache.getOperationFileContent(hashCode);
                            // loading the operation into the cache
                            m_cache.load(operation::SolverOperation(hashCode, solutionString));
                        } catch (...) {
                            status = 5;
                        }

                    } else {
                        // getting the right solver according to the specific command, using a solver factory
                        solver::SolverFactory<Problem, Solution> sFactory = solver::SolverFactory<Problem, Solution>();
                    
                        try {
                            const auto solver = sFactory.getSolver(commandString);
                            solutionString = solver->solve(problemString);
                            // loading the operation into the cache
                            m_cache.load(operation::SolverOperation(hashCode, solutionString));
                        } catch(const status_exception::StatusException& e){
                            status = e.getStatus();
                        } catch (...) {
                            status = 5;
                        }
                    }

                    // the calculation has succeeded
                    if (status == 0) {
                        // send success message
                        try {
                            writeSock(clientSocket, getLog(status, solutionString.size()) + "\r\n" + solutionString);
                        } catch (...) {}

                        try {
                            closeSock(clientSocket);
                        } catch (...) {}
                    }
                    // if the calculation has failed
                    else {
                        // send error message
                        try {
                            writeSock(clientSocket, getLog(status, s_EMPTY_RESPONSE_LENGTH));
                        } catch (...) {}

                        try {
                            closeSock(clientSocket);
                        } catch (...) {}
                    }         
                }

            private:
            
                std::string getLog(uint32_t status, uint32_t length) const {
                    return "Version: " + std::to_string(s_VERSION) + "\r\n"
                    + "status: " + std::to_string(status) + "\r\n"
                    + "response-length: " + std::to_string(length) + "\r\n";
                }
        };
    }
}

