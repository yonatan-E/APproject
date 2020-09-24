#pragma once

#include <stdexcept>
#include <string>

namespace server {

    namespace exceptions {

        /**
         * @brief This class represents a server exception.
         * 
         */
        class ServerException : public std::runtime_error {

            public:

                /**
                 * @brief Construct a new Server Exception object
                 * 
                 */
                ServerException(std::string message);
        };

        /**
         * @brief This class represents an invalid command exception.
         * 
         */
        class InvalidCommandException : public std::runtime_error {

            public:

                /**
                 * @brief Construct a new Invalid Command object
                 * 
                 */
                InvalidCommandException();
        };
    }
}