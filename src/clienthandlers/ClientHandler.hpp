#include "../solvers/Solver.hpp"
#include "memory"

namespace server {

    namespace clienthandler {

        class ClientHandler{
            
            public:
            
                virtual void handleClient(int clientSocket) const = 0;
        };
    }
}