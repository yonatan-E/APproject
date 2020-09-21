#include "ClientHandler.hpp"

namespace server {

    namespace handler {

        template <typename Problem, typename Solution>
        class SolverClientHandler : public ClientHandler{

            const solver::Solver<Problem, Solution>& m_solver;
            const cache::CacheManager m_cache;

            void handleClient(int inputSocket, int outputSocket) const override{

                Solver solver = parseSolver(stringProblem);

                Problem input = solver.parseInput(stringInput);

                if(m_cache.contains(prob,algo)){
                    return m_cache.find(m,algo);
                }

                //solver
                m_solver.solve(input);

                m_cache.add(m,algo);
                

            }

        };


    }
}

