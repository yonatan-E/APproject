#include "SolverFactory.hpp"
#include "../search/searcher/AStarSearcher.hpp"
#include "../search/searcher/BFSSearcher.hpp"
#include "../search/searcher/DFSSearcher.hpp"
#include "../search/searcher/BestFSSearcher.hpp"
#include "../clienthandlers/ServerExceptions.hpp"
#include "../search/searchable/Graph.hpp"
#include <vector>

namespace factories{

    template <>
    std::unique_ptr<solver::Solver<searcher::Graph, searcher::SearchResult>>
    SolverFactory<searcher::Graph, searcher::SearchResult>::getSolver(std::string request) const{

        std::vector<std::string> command;

        std::string curString = "";
        for (int i = 0 ;i < request.size(); i++){
            if(request.at(i) == ' ' && curString.size() > 0){
                command.push_back(curString);
                curString = "";
            }
            if(i == curString.size() - 1){
                command.push_back(curString);
            }
        }

        if (command.size() != 3 && command.size() != 2){
             throw server::exceptions::MessageFormatException();
        }

        std::unique_ptr<solver::SearchSolver> solver;

        //Search Solver

        if(command[0] == "solve" && command[1] == "find-graph-path"){
            if(command.size() == 2 || command[2] == "BestFS"){
                solver = std::make_unique<solver::SearchSolver>(searcher::BestFSSearcher<std::pair<uint32_t, uint32_t>>());
            }
            else if(command[2] == "BFS"){
                solver = std::make_unique<solver::SearchSolver>(searcher::BFSSearcher<std::pair<uint32_t, uint32_t>>());
            }
            else if(command[2] == "DFS"){
                solver = std::make_unique<solver::SearchSolver>(searcher::DFSSearcher<std::pair<uint32_t, uint32_t>>());
            }
            else if(command[2] == "A*"){
                solver = std::make_unique<solver::SearchSolver>(searcher::AStarSearcher<std::pair<uint32_t, uint32_t>>());
            }
            else{
                throw server::exceptions::MessageFormatException();
            }
            return solver;
        }

        throw server::exceptions::MessageFormatException();
    }

}