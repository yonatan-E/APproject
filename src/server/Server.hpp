#pragma once

#include "../clienthandlers/ClientHandler.hpp"
#include "../search/searchable/Graph.hpp"
#include "../search/searcher/SearchResult.hpp"
#include "../clienthandlers/SolverClientHandler.hpp"

namespace server_side {

    class Server {

        public:

            virtual void open(uint32_t serverPort, const client_side::ClientHandler& clientHandler) const = 0;

            virtual bool stop() const = 0;

    };

}