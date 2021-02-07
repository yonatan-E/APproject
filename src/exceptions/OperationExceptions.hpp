#pragma once

#include <stdexcept>

namespace operation
{

    namespace exceptions
    {

        /**
         * @brief This class represents a file delete exception.
         * 
         */
        class FileDeleteException : public std::runtime_error
        {

        public:
            /**
                 * @brief Construct a new File Delete Exception object
                 * 
                 */
            FileDeleteException();
        };

        /**
         * @brief This class represents a file open exception.
         * 
         */
        class FileOpenException : public std::runtime_error
        {

        public:
            /**
                 * @brief Construct a new File Open Exception object
                 * 
                 */
            FileOpenException();
        };

        /**
         * @brief This class represents a file write exception.
         * 
         */
        class FileWriteException : public std::runtime_error
        {

        public:
            /**
                 * @brief Construct a new File Write Exception object
                 * 
                 */
            FileWriteException();
        };

        /**
         * @brief This class represents a file read exception.
         * 
         */
        class FileReadException : public std::runtime_error
        {

        public:
            /**
                 * @brief Construct a new File Read Exception object
                 * 
                 */
            FileReadException();
        };
    }
}