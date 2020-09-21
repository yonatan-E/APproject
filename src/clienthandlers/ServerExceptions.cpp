#include "ServerExceptions.hpp"

namespace server {

    namespace exceptions {
        
        MessageFormatException::MessageFormatException()
            : std::runtime_error("Invalid message format") {}
    }
}