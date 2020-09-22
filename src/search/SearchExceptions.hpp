#pragma once

#include <stdexcept>
#include <string>

namespace searcher {

    namespace exceptions {

        class InvalidPositionException : public std::runtime_error {

            public:

                InvalidPositionException(std::string message);
        };

        class PathDoesNotExistException : public std::runtime_error {

            public:

                PathDoesNotExistException();
        };
    }
}