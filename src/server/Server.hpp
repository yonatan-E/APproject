#include "ClientHandler.hpp"
#include "../search/searchable/Graph.hpp"
#include "../search/searcher/SearchResult.hpp"

namespace server{

    template <typename Problem, typename Solution>
    class Server{

        virtual void open(uint32_t serverPort, const clientside::ClientHandler<Problem, Solution>& clientHandler) const;

        virtual void stop() const;

    };

}