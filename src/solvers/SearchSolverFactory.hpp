#pragma once

#include "SolverFactory.hpp"
#include "SearchSolver.hpp"

namespace solver {

    class SearchSolverFactory : public SolverFactory<searcher::Graph, searcher::SearchResult> {

        /**
             * @brief Create a solver according to a specific command.
             * 
             * @param command the given command
             * @return std::unique_ptr<solver::Solver<Problem, Solution>> a pointer to a solver, which was created
             *      according to the given command
             */
        std::unique_ptr<solver::Solver<searcher::Graph, searcher::SearchResult>>
        getSolver(const std::string &command) const override;
    };
}