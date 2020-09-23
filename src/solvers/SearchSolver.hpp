#pragma once

#include "Solver.hpp"
#include "../search/searcher/Searcher.hpp"
#include "../search/searcher/SearchResult.hpp"
#include "../search/searchable/Graph.hpp"
#include <cstdint>
#include <utility>
#include <memory>

namespace solver {

    class SearchSolver : public Solver<searcher::Graph, searcher::SearchResult> {

        std::unique_ptr<searcher::Searcher<searcher::SearchResult, std::pair<uint32_t, uint32_t>>> m_searcher;

        public:

            SearchSolver(std::unique_ptr<searcher::Searcher<searcher::SearchResult, std::pair<uint32_t, uint32_t>>> searcher);

            std::string solve(const std::string& problemString) const override;
    };
}