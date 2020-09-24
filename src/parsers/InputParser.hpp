#pragma once

#include <string>

namespace parser {

    /**
     * @brief This class represents an input parser.
     * 
     * @tparam Input the type of the object that the input will be parsed to.
     */
    template <typename Input>
    class InputParser {

        public:
            
            /**
             * @brief Parse an input string to an actual object of type Input
             * 
             * @param input the given input string
             * @return Input the object that the given input string was parsed to
             */
            virtual Input parseInput(const std::string& input) const = 0;
    };
}