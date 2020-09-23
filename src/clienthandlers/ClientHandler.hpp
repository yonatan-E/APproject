#include "../solvers/Solver.hpp"
#include "memory"

namespace server {

    namespace clientside {

        class ClientHandler{
            
            public:
            
                virtual void handleClient(uint32_t clientSocket) const = 0;
        };
    }
}