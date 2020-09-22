#include "../solvers/Solver.hpp"
#include "../solvers/SearchSolver.hpp"
#include <string>
#include <memory>

namespace factories{

    template <typename Problem, typename Solution >
    class SolverFactory{

        std::unique_ptr<solver::Solver<Problem, Solution>> getSolver(const std::string& command) const;

    };
}