#pragma once

#include <stdexcept>

namespace server {

    namespace exceptions {

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