#include "ClientHandler.hpp"
#include "../solvers/Solver.hpp"
#include "../solvers/SearchSolver.hpp"

namespace server {

    namespace handler {

        template <typename Problem, typename Solution>
        class SolverClientHandler : public ClientHandler{

            cache::CacheManager m_cache;
            const int m_bufferSize = 1000000;
            const double m_version = 1.0;

            void handleClient(const int inputSocket, const int outputSocket) const override{

                std::string stringProblem = readSock(inputSocket);
                std::string stringInput = readSock(inputSocket);
                std::string result;

                solver<Problem, Solution> solver = parseSolver(stringProblem);

                Problem input = solver.parseInput(stringInput);

                //add cache managing

                try{
                    result = m_solver.solve(input);
                }
                catch(const searcher::exceptions::PathDoesNotExistException&){
                    result = printLog(1, 0);
                }
                catch(const searcher::exceptions::InvalidStartPositionException&){
                    result =  printLog(2, 0);
                }
                 catch(const searcher::exceptions::InvalidEndPositionException&){
                    result = printLog(3, 0);
                }
                catch(const searcher::exceptions::MessageFormatException&){
                    result = printLog(4, 0);
                }

                writeSock(outputSocket, result);

                closeSock(inputSocket, outputSocket);
                
            }

            void closeSock(const int inputSocket, const int outputSocket){
                close(inputSocket);
                if(inputSocket != outputSocket()){
                    close(outputSocket);
                }
            }

            void writeSock(const int outputSocket, std::string message){
                write(outputSocket, message.c_str(), message.size() + 1);
            }

            std::string readSock(const int inputSocket) const{
                char buffer[m_bufferSize];
                size_t bytesRead;
                int messageSize = 0;

                while(bytesRead == read(inputSocket, buffer + messageSize, sizeof(buffer) - messageSize - 1) > 0){
                    messageSize += bytesRead;

                    if(messageSize > bufferSize - 1){
                        //fail backlog and close connection
                    }

                    if(buffer[messageSize - 1] = "\r\n\r\n"){
                        break;
                    }
                }

                if(bytesRead < 0){
                    //fail backlog and close connection 
                }

                //Succes backlog

                return (std::string) buffer;
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

