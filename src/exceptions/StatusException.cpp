#include "StatusException.hpp"

namespace status_exception
{

    StatusException::StatusException(std::string message, const uint32_t status)
        : std::runtime_error(std::move(message)),
          m_status(status) {}

    uint32_t StatusException::getStatus() const noexcept
    {
        return m_status;
    }
}