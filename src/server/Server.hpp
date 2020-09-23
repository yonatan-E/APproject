#include "ClientHandler.hpp"
#include "../search/searchable/Graph.hpp"
#include "../search/searcher/SearchResult.hpp"
#include "../clienthandlers/SolverClientHandler.hpp"

namespace server{

    class Server{

        virtual void open(uint32_t serverPort, const clientside::ClientHandler& clientHandler) const;

        virtual bool stop() const;

    };

}