#include "ServerExceptions.hpp"

namespace server {

    namespace exceptions {

        ServerException::ServerException(std::string message)
        : std::runtime_error(std::move(message)) {}
    }
}