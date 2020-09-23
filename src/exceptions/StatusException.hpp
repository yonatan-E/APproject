#pragma once

#include <stdexcept>
#include <string>
#include <cstdint>

namespace status_exception {

    class StatusException : public std::runtime_error {

        const uint32_t m_status;

        public:

            StatusException(std::string message, const uint32_t status);

            uint32_t getStatus() const noexcept;
    };
}