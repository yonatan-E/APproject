#pragma once

#include "AbstractClientHandler.hpp"
#include "Solver.hpp"
#include "Parser.hpp"
#include "CacheManager.hpp"
#include "SolverOperation.hpp"
#include "StatusException.hpp"
#include "HashUtil.hpp"

#include <memory>
#include <sys/socket.h>

namespace server_side {

    namespace client_handler {
        
        /**
         * @brief This class represents a client handler which handle the client using a specific solver.
         * 
         * @tparam Problem the type problem type of the solver
         * @tparam Solution the solution type of the solver
         */
        template <typename Problem, typename Solution>
        class SolverClientHandler : public AbstractClientHandler {

            // the version
            static constexpr int s_VERSION = 1.0;
            // the status for success
            static constexpr int s_SUCCESS_STATUS = 0;
            // the length of an empty response
            static constexpr const char* s_EMPTY_RESPONSE = "";

            // the solver factory, used to create the concrete solver
            std::unique_ptr<parser::Parser<std::unique_ptr<solver::Solver<Problem, Solution>>>> m_commandParser;
            // the input parser, used to parse the input problem
            std::unique_ptr<parser::Parser<Problem>> m_inputParser;
            // the cache manager used to save previous solutions
            mutable cache::CacheManager m_cacheManager;

            public:

                /**
                 * @brief Construct a new Solver Client Handler object
                 * 
                 * @param commandParser the given command parser
                 * @param inputParser the given input parser
                 * @param cache the given cache manager
                 */
                SolverClientHandler(
                    std::unique_ptr<parser::Parser<std::unique_ptr<solver::Solver<Problem, Solution>>>> commandParser,
                    std::unique_ptr<parser::Parser<Problem>> inputParser,
                    const cache::CacheManager& cacheManager);

                /**
                 * @brief Handle a specific client
                 * 
                 * @param clientSocket the client socket
                 */
                void handleClient(int clientSocket) const override;

            private:

                /**
                 * @brief Read the content of a client socket, with a timeout of 5 seconds.
                 * 
                 * @param clientSocket the given client socket
                 * @return std::string a string with the content of the client socket
                 */
                std::string readSockWithTimeout(int clientSocket) const;
        };

        template <typename Problem, typename Solution>
        SolverClientHandler<Problem, Solution>::SolverClientHandler(
            std::unique_ptr<parser::Parser<std::unique_ptr<solver::Solver<Problem, Solution>>>> commandParser,
            std::unique_ptr<parser::Parser<Problem>> inputParser,
            const cache::CacheManager& cacheManager)
        : m_commandParser(std::move(commandParser)),
        m_inputParser(std::move(inputParser)),
        m_cacheManager(cacheManager) {}

        template <typename Problem, typename Solution>
        void SolverClientHandler<Problem, Solution>::handleClient(const int clientSocket) const {

            // reading the command string
            std::string commandString;
            try {
                commandString = readSockWithTimeout(clientSocket);
            } catch (...) {
                return;
            }

            // if the message was sent by the client successfully, then sending a success log
            try {
                writeSock(clientSocket, getLog(s_VERSION, s_SUCCESS_STATUS, s_EMPTY_RESPONSE));
            } catch (...) {

                // if couldn't write, then closing the socket
                try {
                    closeSock(clientSocket);
                } catch (...) {}

                return;
            }

            // reading the problem string
            std::string problemString;
            try {
                problemString = readSockWithTimeout(clientSocket);
            } catch (...) {
                return;
            }

            // success in recieving input, solving the problem with the input.
            // this variable will hold the solution, as string
            std::string solutionString;
            // this variable will hold the status of the solving
            int status = 0;

            // first, searching for the solution in the cache:
            // getting the hashCode of the operation
            const uint32_t hashCode = util::HashUtil::calculateHash(commandString + problemString);
            // if the operation result also exists in the cache, so getting it from the cache
            if (m_cacheManager.contains(hashCode)) {
                try {
                    solutionString = m_cacheManager.getOperationFileContent(hashCode);
                    // loading the operation into the cache
                    m_cacheManager.load(operation::SolverOperation(hashCode, solutionString));
                } catch (...) {
                    status = 5;
                }
            } else {
                try {
                    const auto solver = m_commandParser->parse(commandString);
                    const auto problem = m_inputParser->parse(problemString);
                    solutionString = solver->solve(problem).toString();
                    // loading the operation into the cache
                    m_cacheManager.load(operation::SolverOperation(hashCode, solutionString));
                } catch (const status_exception::StatusException& e) {
                    status = e.getStatus();
                } catch (...) {
                    status = 5;
                }
            }

            // the calculation has succeeded
            if (status == 0) {
                // sending a success message
                try {
                    writeSock(clientSocket, getLog(s_VERSION, status, solutionString) + "\r\n");
                } catch (...) {}
            }
            // if the calculation has failed
            else {
                // sending a error message
                try {
                    writeSock(clientSocket, getLog(s_VERSION, status, s_EMPTY_RESPONSE) + "\r\n");
                } catch (...) {}
            }
            // closing the connection
            try {
                closeSock(clientSocket);
            } catch (...) {}
        }

        template <typename Problem, typename Solution>
        std::string SolverClientHandler<Problem, Solution>::readSockWithTimeout(const int clientSocket) const {
            try {
                // setting the timeout for the socket
                struct timeval tv = {5, 0};
                setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<struct timeval *>(&tv), sizeof(struct timeval));

                return readSock(clientSocket);

            } catch (const status_exception::StatusException& e) {

                // if couldn't read from the socket, then sending error log and closing the connection.
                // checking that the error is not about the timeout, because if the error is about the timeout,
                // then the server will not send a message to the client
                if (errno != EWOULDBLOCK) {
                    try {
                        writeSock(clientSocket, getLog(s_VERSION, e.getStatus(), s_EMPTY_RESPONSE));
                    } catch (...) {}
                }
                // closing the connection
                try {
                    closeSock(clientSocket);
                } catch (...) {}
                
                throw e;
            }
        }
    }
}