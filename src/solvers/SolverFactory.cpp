#include "SolverFactory.hpp"
#include "../search/searcher/AStarSearcher.hpp"
#include "../search/searcher/BFSSearcher.hpp"
#include "../search/searcher/DFSSearcher.hpp"
#include "../search/searcher/BestFSSearcher.hpp"
#include "../clienthandlers/ServerExceptions.hpp"
#include "../search/searchable/Graph.hpp"
#include <vector>

namespace solver {

    template <>
    std::unique_ptr<solver::Solver<searcher::Graph, searcher::SearchResult>>
    SolverFactory<searcher::Graph, searcher::SearchResult>::getSolver(const std::string& command) const {

        std::vector<std::string> commandParts;

        std::string it = "";
        for (int i = 0; i < command.size(); i++){
            if (command.at(i) != ' ') {
                it += command.at(i);
                if(i == it.size() - 1){
                commandParts.push_back(it);
                }
            }
            else if (it.size() > 0) {
                commandParts.push_back(it);
                it = "";
            }
        }

        if (command.size() != 3 && command.size() != 2){
            throw server::exceptions::InvalidCommandException();
        }

        std::unique_ptr<solver::SearchSolver> solver;

        if(commandParts[0] == "solve" && commandParts[1] == "find-graph-path"){
            if(commandParts.size() == 2 || commandParts[2] == "BestFS") {
                solver = std::make_unique<solver::SearchSolver>(searcher::BestFSSearcher<std::pair<uint32_t, uint32_t>>());
            }
            else if(commandParts[2] == "BFS"){
                solver = std::make_unique<solver::SearchSolver>(searcher::BFSSearcher<std::pair<uint32_t, uint32_t>>());
            }
            else if(commandParts[2] == "DFS"){
                solver = std::make_unique<solver::SearchSolver>(searcher::DFSSearcher<std::pair<uint32_t, uint32_t>>());
            }
            else if(commandParts[2] == "A*"){
                solver = std::make_unique<solver::SearchSolver>(searcher::AStarSearcher<std::pair<uint32_t, uint32_t>>());
            }
            else {
                throw server::exceptions::InvalidCommandException();
            }
            return solver;
        }

        throw server::exceptions::InvalidCommandException();
    }

}