#pragma once

#include <stdexcept>
#include <string>
#include <cstdint>

namespace status_exception
{

    /**
     * @brief This class represents an exceptions that can hold a message and a status.
     * 
     */
    class StatusException : public std::runtime_error
    {

        // the status of the exception
        const uint32_t m_status;

    public:
        /**
             * @brief Construct a new Status Exception object
             * 
             * @param message the message of the exception
             * @param status the status of the exceptioon
             */
        StatusException(std::string message, uint32_t status);

        /**
             * @brief Get the status of the exception
             * 
             * @return uint32_t the status of the exception
             */
        uint32_t getStatus() const noexcept;
    };
}