#pragma once

#include <string>

namespace solver
{

    /**
     * @brief This class represents a problem solver.
     * 
     * @tparam Problem the type of the problem
     * @tparam Solution the type of the solution
     */
    template <typename Problem, typename Solution>
    class Solver
    {

    public:
        /**
             * @brief Solve a problem and get its solution
             * 
             * @param problemString a string represents the given problem
             * @return std::string a string represents the solution of the given problem
             */
        virtual std::string solve(const std::string &problemString) const = 0;

        /**
         * @brief Virtual destructor
         * 
         */
        virtual ~Solver() = default;
    };
}