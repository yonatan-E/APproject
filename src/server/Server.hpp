#include "ClientHandler.hpp"
#include "SolverClientHandler.hpp"
#include "../search/searchable/Graph.hpp"
#include "../search/searcher/SearchResult.hpp"

namespace server{

    template <typename Problem, typename Solution>
    class Server{

        virtual void open(int serverPort, const Clienthandler<Problem, Solution>& clientHandler) const;

    };

}