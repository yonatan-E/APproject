#pragma once

#include "Solver.hpp"
#include "Searcher.hpp"
#include "Graph.hpp"
#include "SearchResult.hpp"
#include "SearcherInputParser.hpp"

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