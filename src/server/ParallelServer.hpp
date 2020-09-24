#pragma once

#include "Server.hpp"
#include "../search/searchable/Graph.hpp"
#include "../search/searcher/SearchResult.hpp"
#include "../clienthandlers/SolverClientHandler.hpp"
#include <queue>
#include <vector>
#include <thread>
#include <mutex>

namespace server_side{
    class ParallelServer: public Server{

         const uint32_t m_backlog = 100;
         const uint32_t m_threadPoolSize = 20;
         mutable std::queue<uint32_t> m_waitingClients;
         mutable std::vector<std::thread> m_threadPool;

        public:

            void open(uint32_t serverPort, const client_handler::ClientHandler& clientHandler) const override;

            bool stop() const override;
    };
    
}
