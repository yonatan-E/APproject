#pragma once

#include "ClientHandler.hpp"
#include <string>

namespace server_side {

    namespace client_handler {

        class AbstractClientHandler : public ClientHandler {

            static constexpr uint32_t s_BUFFER_SIZE = 100000;

            public:

                virtual void handleClient(const uint32_t clientSocket) const = 0;

            protected:

                virtual std::string readSock(const uint32_t clientSocket) const;

                virtual void writeSock(const uint32_t clientSocket, const std::string& message) const;

                virtual void closeSock(const uint32_t clientSocket) const;
        };
    }
}