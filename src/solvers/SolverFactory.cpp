#include "SolverFactory.hpp"
#include "../search/searcher/AStarSearcher.hpp"
#include "../search/searcher/BFSSearcher.hpp"
#include "../search/searcher/DFSSearcher.hpp"
#include "../search/searcher/BestFSSearcher.hpp"
#include "../exceptions/StatusException.hpp"
#include "../search/searchable/Graph.hpp"
#include <vector>

namespace solver {

    template <>
    std::unique_ptr<solver::Solver<searcher::Graph, searcher::SearchResult>>
    SolverFactory<searcher::Graph, searcher::SearchResult>::getSolver(const std::string& command) const {

        // parsing the command into parts
        std::vector<std::string> commandParts;
        std::string part = "";
        for (const auto x : command) {
            if (x == ' ') {
                if (part.size() > 0) {
                    commandParts.push_back(part);
                }
                part = "";
            } else {
                part += x;
            }
        }

        // checking if the command length is legal
        if (command.size() != 3 && command.size() != 2){
            throw status_exception::StatusException("Invalid message length", 4);
        }

        // getting the right searcher, according to the command
        // and throwing exceptions in case that the command is invalid
        std::unique_ptr<solver::SearchSolver> solver;
        if (commandParts[0] == "solve" && commandParts[1] == "find-graph-path") {
            if(commandParts.size() == 2 || commandParts[2] == "BestFS") {
                solver = std::make_unique<solver::SearchSolver>(searcher::BestFSSearcher<std::pair<uint32_t, uint32_t>>());
            }
            else if (commandParts[2] == "BFS") {
                solver = std::make_unique<solver::SearchSolver>(searcher::BFSSearcher<std::pair<uint32_t, uint32_t>>());
            }
            else if (commandParts[2] == "DFS") {
                solver = std::make_unique<solver::SearchSolver>(searcher::DFSSearcher<std::pair<uint32_t, uint32_t>>());
            }
            else if (commandParts[2] == "A*") {
                solver = std::make_unique<solver::SearchSolver>(searcher::AStarSearcher<std::pair<uint32_t, uint32_t>>());
            }
            else {
                throw status_exception::StatusException("Invalid algorithm name", 4);
            }
            return solver;
        }
        
        throw status_exception::StatusException("Invalid problem type", 4);
    }
}