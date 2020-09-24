#pragma once

#include <stdexcept>
#include <string>

namespace parser
{

    namespace exceptions
    {

        /**
         * @brief This class represents an invalid parser input exception.
         * 
         */
        class InvalidInputException : public std::runtime_error
        {

        public:
            /**
                 * @brief Construct a new Invalid Input Exception object
                 * 
                 * @param message the message of the exception
                 */
            InvalidInputException(std::string message);
        };
    }
}