#include "SolverFactory.hpp"
#include "SearchSolver.hpp"
#include "../search/searcher/AStarSearcher.hpp"
#include "../search/searcher/BFSSearcher.hpp"
#include "../search/searcher/DFSSearcher.hpp"
#include "../search/searcher/BestFSSearcher.hpp"
#include "../exceptions/StatusException.hpp"
#include <vector>

namespace solver {

    // concrete implementation in case that the solver is a search solver
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
                if(x == command.at(command.size() - 1)){
                    commandParts.push_back(part);
                }
            }
        }

        // checking if the command length is legal
        if (commandParts.size() != 3 && commandParts.size() != 2){
            throw status_exception::StatusException("Invalid message length", 3);
        }

        // getting the right searcher, according to the command
        // and throwing exceptions in case that the command is invalid

        if (commandParts[0] == "solve" && commandParts[1] == "find-graph-path") {
            if(commandParts.size() == 2 || commandParts[2] == "BestFS") {
                return std::make_unique<solver::SearchSolver>(std::make_unique<searcher::BestFSSearcher<std::pair<uint32_t, uint32_t>>>());
            }
            else if (commandParts[2] == "BFS") {
                return std::make_unique<solver::SearchSolver>(std::make_unique<searcher::BFSSearcher<std::pair<uint32_t, uint32_t>>>());
            }
            else if (commandParts[2] == "DFS") {
                return std::make_unique<solver::SearchSolver>(std::make_unique<searcher::DFSSearcher<std::pair<uint32_t, uint32_t>>>());
            }
            else if (commandParts[2] == "A*") {
                return std::make_unique<solver::SearchSolver>(std::make_unique<searcher::AStarSearcher<std::pair<uint32_t, uint32_t>>>());
            }
            else {
                throw status_exception::StatusException("Invalid algorithm name", 3);
            }
        }
        
        throw status_exception::StatusException("Invalid problem type", 3);
    }
}