#pragma once

#include <stdexcept>

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
        class MessageFormatException : public std::runtime_error {

            public:

                /**
                 * @brief Construct a new Message Format Exception object
                 * 
                 */
                MessageFormatException();
        };
    }
}