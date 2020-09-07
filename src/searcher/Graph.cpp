#include "Graph.hpp"

namespace searcher {

    Graph::Graph(const matrix::Matrix& graphMatrix, const pair& startLocation, const pair& endLocation)
    : AbstractSearchable(graphElement(startLocation, graphMatrix(startLocation.first, startLocation.second)), 
    graphElement(endLocation, graphMatrix(endLocation.first, endLocation.second))), 
    m_graphMatrix(graphMatrix) {}

    std::vector<graphElement> Graph::getAllReachableElements(const graphElement& current) const {
        // this vector will contain the elements which can be reached from the current element
        std::vector<graphElement> reachables;

        // getting the exact location of the current element
        uint32_t rowIdx = current.getIdentifier().first;
        uint32_t colIdx = current.getIdentifier().second;

        // adding the element above the current element, if exists
        if (rowIdx > 0) {
            reachables.push_back(graphElement(pair(rowIdx - 1, colIdx), m_graphMatrix(rowIdx - 1, colIdx)));
        }

        // adding the element below the current element, if exists
        if (rowIdx < m_graphMatrix.getHeight() - 1) {
            reachables.push_back(graphElement(pair(rowIdx + 1, colIdx), m_graphMatrix(rowIdx + 1, colIdx)));
        }

        // adding the element in the left of the current element, if exists
        if (colIdx > 0) {
            reachables.push_back(graphElement(pair(rowIdx, colIdx - 1), m_graphMatrix(rowIdx, colIdx - 1)));
        }

        // adding the element in the right of the current element, if exists
        if (colIdx < m_graphMatrix.getWidth() - 1) {
            reachables.push_back(graphElement(pair(rowIdx, colIdx + 1), m_graphMatrix(rowIdx, colIdx + 1)));
        }

        return reachables;
    }
}