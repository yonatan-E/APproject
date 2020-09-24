#pragma once

#include "InputParser.hpp"
#include "../search/searchable/Graph.hpp"

namespace parser {

    /**
     * @brief This class represents a graph input parser.
     * 
     */
    class GraphInputParser : public InputParser<searcher::Graph> {

        public:

            /**
             * @brief Parse an input string to a Graph object
             * 
             * @param input the given input string
             * @return searcher::Graph the graph object that the given input string was parsed to
             */
            searcher::Graph parseInput(const std::string& input) const;
    };
}