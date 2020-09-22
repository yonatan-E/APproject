#include "ClientHandler.hpp"
#include "../solvers/Solver.hpp"
#include "../solvers/SearchSolver.hpp"
#include "ServerExceptions.hpp"

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
                SolverFactory factory = SolverFactory();
                solver<Problem, Solution> solver& = factory.getSolver(stringProblem);

                //parse the input according to the solver
                Problem input = solver.parseInput(stringInput);

                //add cache managing here

                std::string result;

                //trying to solve the problem, return error message if one accurs
                try {
                    result = m_solver.solve(problem);
                }
                catch(const searcher::exceptions::PathDoesNotExistException&){
                    result = printLog(1, m_noResponseLength);
                }
                catch(const searcher::exceptions::InvalidStartPositionException&){
                    result =  printLog(2, m_noResponseLength);
                }
                 catch(const searcher::exceptions::InvalidEndPositionException&){
                    result = printLog(3, m_noResponseLength);
                }
                catch(const server::exceptions::MessageFormatException&){
                    result = printLog(4, m_noResponseLength);
                }

                //success, write a success message and the result to the client
                writeSock(clientSocket,  getLog(m_successStatus, result.size()));
                writeSock(clientSocket, result);

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

