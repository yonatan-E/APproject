#pragma once

#include "Solver.hpp"
#include <memory>

namespace solver
{

    /**
    * @brief This class is a factory of solver objects.
    * 
    */
    template <typename Problem, typename Solution>
    class SolverFactory
    {

    public:
        /**
             * @brief Create a solver according to a specific command.
             * 
             * @param command the given command
             * @return std::unique_ptr<solver::Solver<Problem, Solution>> a pointer to a solver, which was created
             *      according to the given command
             */
        std::unique_ptr<solver::Solver<Problem, Solution>> getSolver(const std::string &command) const;
    };
}