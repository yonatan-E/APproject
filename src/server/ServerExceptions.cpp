#include "ServerExceptions.hpp"

namespace server {

    namespace exceptions {

        InvalidCommandException::InvalidCommandException()
            : std::runtime_error("Invalid command") {}
        
        ProtocolException::ProtocolException(std::string message)
            : std::runtime_error(std::move(message)) {}
    }
}