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
         mutable std::queue<uint32_t> waitingClients;
         mutable std::unique_lock<std::mutex> mutexLock;
         mutable std::vector<std::thread> threadPool;

        public:

            void clientHandle(const client_handler::ClientHandler& ch);

            void open(uint32_t serverPort, const client_handler::ClientHandler& clientHandler) const override;

            bool stop() const override;
    };
    
}
