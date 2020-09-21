#include "ClientHandler.hpp"

namespace server {

    namespace handler {

        template <typename Searchable, typename Searcher>
        class AlgorithmClientHandler : public ClientHandler{

            AlgorithmClientHandler(const Solver& solver);

            template <typename int, typename int>
            virtual void handleClient(int inputSocket, int outputSocket) const;
        };
    }
}