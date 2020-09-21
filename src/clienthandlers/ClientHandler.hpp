#include "../solvers/Solver.hpp"
#include "memory"

namespace server {

    namespace clienthandler {


        class ClientHandler{
            
            virtual void handleClient(int inputSocket, int outputSocket) const = 0;

        };
    }
}