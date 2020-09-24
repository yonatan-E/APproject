#include "ServerExceptions.hpp"

namespace server_side
{

    namespace exceptions
    {

        ServerException::ServerException(std::string message)
            : std::runtime_error(std::move(message)) {}

        InvalidCommandException::InvalidCommandException()
            : std::runtime_error("Invalid command") {}
    }
}