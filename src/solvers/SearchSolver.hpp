#pragma once

#include "Solver.hpp"
#include "Searcher.hpp"
#include "SearchResult.hpp"
#include "Graph.hpp"
#include <cstdint>
#include <utility>
#include <memory>

namespace solver
{

    /**
     * @brief This class represents a search problems solver
     * 
     */
    class SearchSolver : public Solver<searcher::Graph, searcher::SearchResult>
    {

        // a pointer to the specific searcher uses to solve the search problem
        std::unique_ptr<searcher::Searcher<searcher::SearchResult, std::pair<uint32_t, uint32_t>>> m_searcher;

    public:
        /**
             * @brief Construct a new Search Solver object
             * 
             * @param searcher a pointer to the specific searcher that will be used to solve the search problem
             */
        SearchSolver(std::unique_ptr<searcher::Searcher<searcher::SearchResult, std::pair<uint32_t, uint32_t>>> searcher);

        /**
             * @brief Solve a problem and get its solution
             * 
             * @param problemString a string represents the given problem
             * @return std::string a string represents the solution of the given problem
             */
        std::string solve(const std::string &problemString) const override;
    };
}