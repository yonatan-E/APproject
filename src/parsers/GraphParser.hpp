#pragma once

#include "Parser.hpp"
#include "Graph.hpp"

namespace parser
{

    /**
     * @brief This class represents a string parser, that parses to a graph object.
     * 
     */
    class GraphParser : public Parser<searcher::Graph>
    {

    public:
        /**
             * @brief Parse an input string to a Graph object
             * 
             * @param input the given input string
             * @return searcher::Graph the graph object that the given input string was parsed to
             */
        searcher::Graph parseInput(const std::string &input) const;
    };
}