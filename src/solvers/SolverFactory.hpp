#pragma once

#include "../solvers/SearchSolver.hpp"
#include <memory>

namespace solver {

    template <typename Problem, typename Solution>
    class SolverFactory {

        std::unique_ptr<solver::Solver<Problem, Solution>> getSolver(const std::string& command) const;

    };
}