#pragma once

#include <string>

namespace parser
{

    /**
     * @brief This class represents a string parser.
     * 
     * @tparam Type the type of the object that the input will be parsed to.
     */
    template <typename Type>
    class Parser
    {

    public:
        /**
             * @brief Parse an input string to an actual object of type Input
             * 
             * @param input the given input string
             * @return Input the object that the given input string was parsed to
             */
        virtual Type parseInput(const std::string &input) const = 0;

        /**
         * @brief Virtual destructor
         * 
         */
        virtual ~Parser() = default;
    };
}