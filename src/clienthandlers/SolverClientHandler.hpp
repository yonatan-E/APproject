#include "ClientHandler.hpp"
#include "../solvers/Solver.hpp"
#include "../solvers/SearchSolver.hpp"
#include "ServerExceptions.hpp"
#include "../factories/SolverFactory.hpp"
#include "../cachemanager/CacheManager.hpp"
#include "../cachemanager/SolverOperation.hpp"
#include <unistd.h>
#include <string>

namespace server {

    namespace client_side {

        template <typename Problem, typename Solution>
        class SolverClientHandler : public ClientHandler{

            mutable cache::CacheManager m_cache;
            const int m_bufferSize = 1000000;
            const double m_version = 1.0;
            const double m_noResponseLength = 0;
            const double m_successStatus = 0;
            const int m_NoPathStatus = 0;

            SolverClientHandler(const cache::CacheManager& cache)
            : m_cache(cache) {}

            void handleClient(const int clientSocket) const override{

                //read problem
                std::string command = readSock(clientSocket);

                //error in recieving problem
                if(command == ""){
                    writeSock(clientSocket, getLog(6, m_noResponseLength));
                    close(clientSocket);
                    return;
                }

                //success in recieving problem
                writeSock(clientSocket, getLog(m_successStatus, m_noResponseLength);

                //read input
                std::string problemString = readSock(clientSocket);

                //error in recieving input
                if(problemString == ""){
                    writeSock(clientSocket, getLog(6, m_noResponseLength));
                    close(clientSocket);
                    return;
                }

                // success in recieving input, solving the problem with the input.
                // this variable will hold the solution, as string
                std::string solutionString;
                // this variable will hold the status of the solving
                uint32_t status = 0;

                // first, searching for the solution in the cache:
                // getting the hashCode of the operation
                const uint32_t hashCode = calculateSolverOperationHashCode(problemString);
                // if the operation result also exists in the cache, so getting it from the cache
                if (m_cache.contains(hashCode)) {
                    try {
                        solutionString = m_cache.getOperationFileContent(hashCode);
                        // loading the operation into the cache
                        m_cache.load(operation::SolverOperation(hashCode, solutionString));
                    } catch (...) {
                        status = 7;
                    }

                } else {
                    //getting the right solver according to the specific command
                    factories::SolverFactory<Problem, Solution> sFactory;
                    const auto solver = sFactory.getSolver(command);

                    //trying to solve the problem, return error message if one accurs
                    try {
                        solutionString = solver->solve(problemString);
                        // loading the operation into the cache
                        m_cache.load(operation::SolverOperation(hashCode, solutionString));
                    }
                    catch(const searcher::exceptions::PathDoesNotExistException&){
                        status = 1;
                    }
                    catch(const searcher::exceptions::InvalidStartPositionException&){
                        status = 2;
                    }
                    catch(const searcher::exceptions::InvalidEndPositionException&){
                        status = 3;
                    }
                    catch(const server::exceptions::InvalidCommandException&){
                        status = 4;
                    }
                    catch(const server::exceptions::MessageFormatException&){
                        status = 5;
                    }
                    catch (...) {
                        status = 7;
                    }
                }

                //the calculation has succeeded
                if(status == 0){
                    //send success message
                    if(writeSock(clientSocket, getLog(status, solutionString.size())) < 0){
                        close(clientSocket);
                        return;
                    }
                    //send solution
                    if(writeSock(clientSocket, solutionString) < 0){
                        close(clientSocket);
                        return;
                    }
                }
                //if the calculation has failed
                else{
                    //send error message
                    if(writeSock(clientSocket, getLog(status, m_noResponseLength)) < 0){
                        close(clientSocket);
                        return;
                    }    
                }

                //close the port
                close(clientSocket);          
            }

            int writeSock(const int clientSocket, std::string message){
                return write(clientSocket, message.c_str(), message.size());
            }

            std::string readSock(const int inputSocket) const{
                
                char buffer[m_bufferSize];
                size_t bytesRead;
                int messageSize = 0;

                while(bytesRead == read(inputSocket, buffer + messageSize, sizeof(buffer) - messageSize - 1) >= 0){
                    messageSize += bytesRead;
                    if(messageSize > m_bufferSize - 1){
                        //fail
                        return "";
                    }
                    if(buffer[messageSize - 1] = "\r\n\r\n"){
                        break;
                    }
                }

                if(bytesRead < 0){
                    //fail
                    return "";
                }
                
                //success
                return static_cast<std::string>(buffer);
            }

            std::string getLog(int status, int length){
                 std::string msg =
                 "Version: " + m_version + "\r\n"
                 "status: " + status + "\r\n"
                 "response-length: " + length + "\r\n";
            }

        };
    }
}

