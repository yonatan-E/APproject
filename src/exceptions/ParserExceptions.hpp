#pragma once

#include <stdexcept>
#include <string>

namespace parser {

    namespace exceptions {

        class InvalidInputException : public std::runtime_error {

            public:

                InvalidInputException(std::string message);
        };
    }
}