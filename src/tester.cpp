#include "server/SerialServer.hpp"
#include "server/ParallelServer.hpp"
#include "clienthandlers/SolverClientHandler.hpp"
#include "search/searcher/SearchResult.hpp"
#include "search/searchable/Graph.hpp"
#include "cachemanager/CacheManager.hpp"

        int main(){

            cache::CacheManager cache(5, "cache");

            server_side::client_handler::SolverClientHandler<searcher::Graph, searcher::SearchResult> handler(cache);

            server_side::ParallelServer serialServer = server_side::ParallelServer();

            serialServer.open(8081, handler);

            return 0;
        }