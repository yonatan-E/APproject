#pragma once

#include "Solver.hpp"
#include "ServerExceptions.hpp"
#include "../search/searcher/Searcher.hpp"
#include "../search/searcher/SearchResult.hpp"
#include "../search/searchable/Searchable.hpp"
#include "../search/searchable/Graph.hpp"
#include "../solvers/Solver.hpp"
#include "../solvers/SearchSolver.hpp"
#include <cstdint>
#include <utility>

namespace solver {

    class SearchSolver : public Solver<searcher::Graph, searcher::SearchResult> {

        const searcher::Searcher<searcher::SearchResult, pair>& m_searcher;

        public:

            SearchSolver(const searcher::Searcher<searcher::SearchResult, pair>& searcher)
            : m_searcher(searcher) {}

            searcher::SearchResult solve(const Graph& problem) const override {
                return m_searcher.search(problem);
            }

            std::string solve(const std::string& problemString) const override {
                parser::SearchInputParser parser;
                searcher::Graph problem = parser.parseInput(problemString);
                return solve(problem).toString();
            }
    };
}