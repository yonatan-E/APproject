#pragma once

#include "Solver.hpp"
#include "../search/searcher/Searcher.hpp"
#include "../search/searcher/SearchResult.hpp"
#include <cstdint>
#include <utility>

namespace solver {

    class SearchSolver : public Solver<searcher::Graph, searcher::SearchResult> {

        const searcher::Searcher<searcher::SearchResult, std::pair<uint32_t, uint32_t>>& m_searcher;

        public:

            SearchSolver(const searcher::Searcher<searcher::SearchResult, std::pair<uint32_t, uint32_t>>& searcher);

            std::string solve(const std::string& problemString) const override;
    };
}