#include "ServerExceptions.hpp"

namespace server {

    namespace exceptions {

        InvalidCommandException::InvalidCommandException()
            : std::runtime_error("Invalid command") {}
        
        MessageFormatException::MessageFormatException()
            : std::runtime_error("Invalid message format") {}
    }
}