#include "server/SerialServer.hpp"
#include "clienthandlers/SolverClientHandler.hpp"
#include "search/searcher/SearchResult.hpp"
#include "search/searchable/Graph.hpp"
#include "cachemanager/CacheManager.hpp"

namespace test{

        int main(){

            cache::CacheManager cm(5, "cache");

            server::clientside::SolverClientHandler<searcher::Graph, searcher::SearchResult> handler(cm);

            server::SerialServer serialServer = server::SerialServer();

            serialServer.open(8989, handler);
            
        }

}