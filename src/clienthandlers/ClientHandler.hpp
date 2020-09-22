#include "../solvers/Solver.hpp"
#include "memory"

namespace server {

    namespace clienthandler {

        class ClientHandler{
            
            virtual void handleClient(int clientSocket) const = 0;
        };
    }
}