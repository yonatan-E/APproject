#include "SerialServer.hpp"
#include "ParallelServer.hpp"
#include "ServerExceptions.hpp"
#include "SolverClientHandler.hpp"
#include "Graph.hpp"
#include "SearchResult.hpp"
#include <vector>
#include <memory>
#include <iostream>

using namespace server_side;

int main(int argc, char *argv[]) {

    // converting the command line arguments into a vector
    std::vector<std::string> command(argv + 1, argv + argc);

    try {

        // checking if the command length is legal, and throwing an exception if it isn't
        if (command.size() != 1 && command.size() != 2) {
            throw exceptions::InvalidCommandException();
        }

        // getting the given port, and throwing an exception if it isn't legal
        uint32_t port;
        try {
            port = std::stoi(command[0]);
        } catch (...) {
            throw exceptions::InvalidCommandException();
        }

        // getting the specific server type according to the command
        std::unique_ptr<Server> server;
        if (command[1] == "serial") {
            server = std::make_unique<SerialServer>();
        } else if (command.size() == 1 || command[1] == "parallel") {
            server = std::make_unique<ParallelServer>();
        } else {
            throw exceptions::InvalidCommandException();
        }

        // creating a cache in size 5, which its files will be stored at the directory "cache"
        cache::CacheManager cache(5, "cache");

        // creating a solver client handler, which solves a search problem
        client_handler::SolverClientHandler<searcher::Graph, searcher::SearchResult> clientHandler(cache);

        // opening and running the server
        server->open(port, clientHandler);

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}