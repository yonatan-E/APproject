#pragma once

#include <string>

namespace parser {

    template <typename Input>
    class InputParser {

        public:
        
            virtual Input parseInput(const std::string& input) const = 0;
    };
}