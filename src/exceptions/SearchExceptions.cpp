#include "SearchExceptions.hpp"

namespace searcher
{

    namespace exceptions
    {

        InvalidPositionException::InvalidPositionException(std::string message)
            : std::runtime_error(std::move(message)) {}

        PathDoesNotExistException::PathDoesNotExistException()
            : std::runtime_error("The requested path does not exist") {}
    }
}