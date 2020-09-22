#pragma once

#include "Solver.hpp"
#include "ServerExceptions.hpp"
#include "../search/searcher/Searcher.hpp"
#include "../search/searcher/SearchResult.hpp"
#include "../search/searchable/Searchable.hpp"
#include "../search/searchable/Graph.hpp"
#include "Solver.hpp"
#include "SearchSolver.hpp"
#include "../parsers/SearcherInputParser.hpp"
#include <cstdint>
#include <utility>

namespace solver {

    class SearchSolver : public Solver<searcher::Graph, searcher::SearchResult> {

        const searcher::Searcher<searcher::SearchResult, std::pair<uint32_t, uint32_t>>& m_searcher;

        public:

            SearchSolver(const searcher::Searcher<searcher::SearchResult, std::pair<uint32_t, uint32_t>>& searcher)
            : m_searcher(searcher) {}

            std::string solve(const std::string& problemString) const override {
                parser::SearcherInputParser parser;
                searcher::Graph problem = parser.parseInput(problemString);
                return (m_searcher.search(problem)).toString();
            }
    };
}