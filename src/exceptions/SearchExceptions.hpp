#pragma once

#include <stdexcept>
#include <string>

namespace searcher {

    namespace exceptions {

        /**
         * @brief This class represents an exception of invalid position in the searchable object.
         * 
         */
        class InvalidPositionException : public std::runtime_error {

            public:

                /**
                 * @brief Construct a new Invalid Position Exception object
                 * 
                 * @param message the message of the exception
                 */
                InvalidPositionException(std::string message);
        };

        /**
         * @brief This class represents an exception of path does not exist in a specific search.
         * 
         */
        class PathDoesNotExistException : public std::runtime_error {

            public:

                /**
                 * @brief Construct a new Path Does Not Exist Exception object
                 * 
                 */
                PathDoesNotExistException();
        };
    }
}