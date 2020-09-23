#include "server/SerialServer.hpp"
#include "clienthandlers/SolverClientHandler.hpp"
#include "search/searcher/SearchResult.hpp"
#include "search/searchable/Graph.hpp"
#include "cachemanager/CacheManager.hpp"

        int main(){

            cache::CacheManager cache(5, "cache");

            server::clientside::SolverClientHandler<searcher::Graph, searcher::SearchResult> handler(cache);

            server::SerialServer serialServer = server::SerialServer();

            serialServer.open(8989, handler);

            return 0;
        }