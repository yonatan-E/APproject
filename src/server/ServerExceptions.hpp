#pragma once

#include <stdexcept>
#include <string>

namespace server {

    namespace exceptions {

        /**
         * @brief This class represents an invalid command exception.
         * 
         */
        class InvalidCommandException : public std::runtime_error {

            public:

                /**
                 * @brief Construct a new Invalid Command Exception object
                 * 
                 */
                InvalidCommandException();
        };

        /**
         * @brief This class represents a message format exception.
         * 
         */
        class ProtocolException : public std::runtime_error {

            public:

                /**
                 * @brief Construct a new Message Format Exception object
                 * 
                 */
                ProtocolException(std::string message);
        };
    }
}