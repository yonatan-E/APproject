#pragma once

#include "Server.hpp"
#include "../search/searchable/Graph.hpp"
#include "../search/searcher/SearchResult.hpp"
#include "../clienthandlers/SolverClientHandler.hpp"

namespace server_side {

    class SerialServer: public Server {

        public:

            virtual void open(uint32_t serverPort, const client_handler::ClientHandler& clientHandler) const override;

            virtual bool stop() const override;
    };
    
}
