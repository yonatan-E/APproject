#include "Graph.hpp"

namespace searcher {

    Graph::Graph(const matrix::Matrix& graphMatrix, const pair& startLocation, const pair& endLocation)
    : Searchable(graphElement(startLocation, graphMatrix(startLocation.first, startLocation.second)), 
    graphElement(endLocation, graphMatrix(endLocation.first, endLocation.second))), 
    m_graphMatrix(graphMatrix) {}

    std::vector<graphElement> Graph::getAllReachableElements(const graphElement& current) const {
        std::vector<graphElement> reachables;
        if ()
    }
}