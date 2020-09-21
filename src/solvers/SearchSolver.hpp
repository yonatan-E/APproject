#pragma once

#include "Solver.hpp"
#include "../search/searchable/Searchable.hpp"
#include "../search/searcher/Searcher.hpp"

namespace solver {

    template <typename Identifier>
    class SearchSolver : public Solver<searcher::Searchable<Identifier>, searcher::SearchResult> {

        const searcher::Searcher<searcher::SearchResult, Identifier>& m_searcher;

        public:

            SearchSolver(const searcher::Searcher<searcher::SearchResult, Identifier>& searcher)
            : m_searcher(searcher) {}

            searcher::SearchResult solve(const searcher::Searchable<Identifier>& problem) const override {
                return m_searcher.search(problem);
            }
    };
}