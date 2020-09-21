#pragma once

namespace solver {

    template <typename Problem, typename Solution>
    class Solver {

        public:

            virtual Solution solve(const Problem& problem) const = 0;

            virtual Problem parseInput(std::string input) const = 0;
    };
}