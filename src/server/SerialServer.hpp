#include "Server.hpp"
#include "../search/searchable/Graph.hpp"
#include "../search/searcher/SearchResult.hpp"
#include "../clienthandlers/SolverClientHandler.hpp"

namespace server{

    class SerialServer: public Server{

        virtual void open(uint32_t serverPort, const clientside::SolverClientHandler<searcher::Graph, searcher::SearchResult>& clientHandler) const;

        virtual void stop() const;
    };
    
}
