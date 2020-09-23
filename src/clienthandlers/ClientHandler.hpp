#include "../solvers/Solver.hpp"
#include "memory"

namespace server {

    namespace clientside {

        class ClientHandler{
            
            public:
            
                virtual void handleClient(int clientSocket) const = 0;
        };
    }
}