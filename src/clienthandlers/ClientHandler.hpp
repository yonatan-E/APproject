#pragma once

#include <cstdint>

namespace server_side
{

    namespace client_handler
    {

        /**
         * @brief This class represents an object that handles a client of the server.
         * 
         */
        class ClientHandler
        {

        public:
            /**
                 * @brief Handle a specific client
                 * 
                 * @param clientSocket the client socket
                 */
            virtual void handleClient(int clientSocket) const = 0;

            /**
             * @brief Virtual destructor
             * 
             */
            virtual ~ClientHandler() = default;
        };
    }
}