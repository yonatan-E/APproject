#include "AbstractClientHandler.hpp"
#include "../exceptions/StatusException.hpp"
#include <unistd.h>

namespace server_side {

    namespace client_handler {

        std::string AbstractClientHandler::readSock(const uint32_t clientSocket) const {
                    
            char buffer[s_BUFFER_SIZE];
            size_t bytesRead;
            int messageSize = 0;

            while (bytesRead == read(clientSocket, buffer + messageSize, sizeof(buffer) - messageSize - 1) >= 0) {
                messageSize += bytesRead;
                if (messageSize > s_BUFFER_SIZE - 1) {
                    throw status_exception::StatusException("Failed writing to socket", 6);
                }
                if (buffer[messageSize - 4] == '\r' && buffer[messageSize - 3] == '\n'
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

        void AbstractClientHandler::writeSock(const uint32_t clientSocket, const std::string& message) const {
            if (write(clientSocket, message.c_str(), message.size()) < 0) {
                throw status_exception::StatusException("Failed writing to socket", 6);
            }
        }

        void AbstractClientHandler::closeSock(const uint32_t clientSocket) const {
            if (close(clientSocket) < 0) {
                throw status_exception::StatusException("Failed writing to socket", 6);
            }
        }
    }
}