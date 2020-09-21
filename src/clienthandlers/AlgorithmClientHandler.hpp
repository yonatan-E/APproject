#include "ClientHandler.hpp"

namespace handler{

    template <typename Searchable, typename Searcher>
    class AlgorihtmClientHandler : public ClientHandler{

        AlgorithmClientHandler(const Solver& solver);

        template <typename int, typename int>
        virtual void handleClient(iStream inputSocket, oStream outputSocket) const;
    };

}
