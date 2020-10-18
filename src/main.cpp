#include "ServerFactory.hpp"
#include "ServerExceptions.hpp"
#include "SolverClientHandler.hpp"
#include "SearchSolverFactory.hpp"
#include "GraphInputParser.hpp"
#include <vector>
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
        ServerFactory serverFactory;
        if (command.size() == 1) {
            server = serverFactory.getDefaultServer();
        } else {
            server = serverFactory.getServer(command[1]);
        }
        
        if (server == nullptr) {
            throw exceptions::InvalidCommandException();
        }

        // creating the solver factory that will be used to create the concrete search solver 
        solver::SearchSolverFactory solverFactory;
        // creating the input parser that will be used to parse the graph input
        parser::GraphInputParser inputParser;
        // creating a cache in size 5, which its files will be stored at the directory "cache"
        cache::CacheManager cacheManager(5, "cache");

        // creating a solver client handler, which solves a search problem
        client_handler::SolverClientHandler<searcher::Graph, searcher::SearchResult> clientHandler(
            std::make_unique<solver::SearchSolverFactory>(solverFactory),
            std::make_unique<parser::GraphInputParser>(inputParser),
            cacheManager);

        // opening and running the server
        server->open(port, clientHandler);

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}