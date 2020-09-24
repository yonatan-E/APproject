#pragma once

#include "Server.hpp"
#include "../search/searchable/Graph.hpp"
#include "../search/searcher/SearchResult.hpp"
#include "../clienthandlers/SolverClientHandler.hpp"

namespace server_side {
    class SerialServer: public Server {

        const uint32_t m_backlog = 100;

        public:

            void open(uint32_t serverPort, const client_handler::ClientHandler& clientHandler) const override;

            bool stop() const override;
    };
    
}
