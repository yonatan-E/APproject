#include "SearchSolver.hpp"
#include "../parsers/GraphInputParser.hpp"

namespace solver {

    SearchSolver::SearchSolver(const searcher::Searcher<searcher::SearchResult, std::pair<uint32_t, uint32_t>>& searcher)
    : m_searcher(searcher) {}

    std::string SearchSolver::solve(const std::string& problemString) const {
        parser::GraphInputParser parser;
        searcher::Graph problem = parser.parseInput(problemString);
        return (m_searcher.search(problem)).toString();
    }
}