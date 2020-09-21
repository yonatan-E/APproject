#include "../solvers/Solver.hpp"
#include "memory"

namespace server {

    namespace clienthandler {

        template <typename Problem, typename Solution>
        class ClientHandler{

            std::unique_ptr<solver::Solver<Problem, Solution>> solver;

            ClientHandler(const Solver& solver) : 
            solver(std::make_unique<solver::Solver<Problem, Solution>>(solver)){}
            
            template <typename iStream, typename oStream>
            virtual void handleClient(iStream input, oStream output) const;

        };
    }
}