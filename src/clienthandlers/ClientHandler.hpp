#pragma once
#include <cstdint>

namespace server_side {

    namespace client_side {

        class ClientHandler {
            
            public:
            
                virtual void handleClient(uint32_t clientSocket) const = 0;
        };
    }
}