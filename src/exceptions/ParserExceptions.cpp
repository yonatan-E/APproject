#include "ParserExceptions.hpp"

namespace parser {

    namespace exceptions {

        InvalidInputException::InvalidInputException(std::string message)
        : std::runtime_error(std::move(message)) {}
    }
}