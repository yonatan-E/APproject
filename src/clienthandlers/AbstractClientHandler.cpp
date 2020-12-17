#include "AbstractClientHandler.hpp"
#include "StatusException.hpp"

#include <unistd.h>
#include <string.h>

namespace server_side {

    namespace client_handler {

        std::string AbstractClientHandler::readSock(const int clientSocket) const {
                    
            char buffer[s_BUFFER_SIZE];
            uint32_t bytesRead = 0;
            uint32_t messageSize = 0;

            bzero(buffer, s_BUFFER_SIZE);

            while ((bytesRead == read(clientSocket, buffer, sizeof(buffer) - 1)) > 0) {

                bzero(buffer, s_BUFFER_SIZE);
                messageSize += bytesRead;
                if (messageSize > s_BUFFER_SIZE - 1) {
                    break;
                }
            }

            if (bytesRead < 0) {
                throw status_exception::StatusException("Failed reading from socket", 6);
            }

            std::string message = static_cast<std::string>(buffer);

            return message.substr(0, message.size() - 4);
        }

        void AbstractClientHandler::writeSock(const int clientSocket, const std::string& message) const {
            if (write(clientSocket, message.c_str(), message.size()) < 0) {
                throw status_exception::StatusException("Failed writing to socket", 6);
            }
        }

        void AbstractClientHandler::closeSock(const int clientSocket) const {
            if (close(clientSocket) < 0) {
                throw status_exception::StatusException("Failed closing the socket", 6);
            }
        }

        std::string AbstractClientHandler::getLog(const double version, const double status, const std::string& message) const {
            return "Version: " + std::to_string(version) + "\r\n"
            + "status: " + std::to_string(status) + "\r\n"
            + "response-length: " + std::to_string(message.size()) + "\r\n"
            + message + "\r\n";
        }
    }
}