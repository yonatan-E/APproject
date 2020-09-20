#pragma once

#include <stdexcept>

namespace searcher {

    namespace exceptions {

        class InvalidStartPositionException : public std::runtime_error {

            public:

                InvalidStartPositionException();
        };

        class InvalidEndPositionException : public std::runtime_error {

            public:

                InvalidEndPositionException();
        };

        class PathDoesNotExistException : public std::runtime_error {

            public:

                PathDoesNotExistException();
        };
    }
}