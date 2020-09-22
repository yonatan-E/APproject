#include "ClientHandler.hpp"
#include "../solvers/Solver.hpp"
#include "../solvers/SearchSolver.hpp"
#include "ServerExceptions.hpp"
#include "../factories/SolverFactory.hpp"

namespace server {

    namespace handler {

        template <typename Problem, typename Solution>
        class SolverClientHandler : public ClientHandler{

            //cache::CacheManager m_cache;
            const int m_bufferSize = 1000000;
            const double m_version = 1.0;
            const double m_noResponseLength = 0;
            const double m_successStatus = 0;
            const int m_NoPathStatus = 0;


            void handleClient(const int clientSocket) const override{

                //read problem
                std::string command = readSock(clientSocket);

                //error in recieving problem
                if(command == nullptr){
                    writeSock(clientSocket, getLog(4, m_noResponseLength));
                    close(clientSocket);
                    return;
                }

                //success in recieving problem
                writeSock(clientSocket, getLog(m_successStatus, m_noResponseLength));

                //read input
                std::string problem = readSock(clientSocket);

                //error in recieving input
                if(problem == nullptr){
                    writeSock(clientSocket, getLog(5, m_noResponseLength));
                    close(clientSocket);
                    return;
                }

                //success in recieving input, solving the problem with the input

                //get the right solver according to the problem request
                SolverFactory sFactory = SolverFactory<Problem, Solution>();
                auto solver = sFactory.getSolver(command);

                //add cache managing here

                std::string result;
                uint32_t status = 0;

                //trying to solve the problem, return error message if one accurs
                try {
                    result = solver->solve(problem);
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

                //send success/fail message
                if(status == 0){
                    writeSock(clientSocket, getLog(status, result.size()));
                }
                else{
                     writeSock(clientSocket, getLog(status, m_noResponseLength));
                }

                //success, send the result
                if(status == 0){
                    writeSock(clientSocket, result);
                }

                //close the port
                close(clientSocket);          
            }

            void writeSock(const int outputSocket, std::string message){
                write(outputSocket, message.c_str(), message.size());
            }

            std::string readSock(const int inputSocket) const{
                
                char buffer[m_bufferSize];
                size_t bytesRead;
                int messageSize = 0;

                while(bytesRead == read(inputSocket, buffer + messageSize, sizeof(buffer) - messageSize - 1) > 0){
                    messageSize += bytesRead;
                    if(messageSize > m_bufferSize - 1){
                        //fail
                        return nullptr;
                    }
                    if(buffer[messageSize - 1] = "\r\n\r\n"){
                        break;
                    }
                }

                if(bytesRead < 0){
                    //fail
                    return nullptr;
                }
                
                //success
                return (std::string) buffer);
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

