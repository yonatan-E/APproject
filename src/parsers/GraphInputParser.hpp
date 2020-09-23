#pragma once

#include "InputParser.hpp"
#include "../search/searchable/Graph.hpp"

namespace parser {

    class GraphInputParser : public InputParser<searcher::Graph> {

        public:

            searcher::Graph parseInput(const std::string& input) const;
    };
}