#include "Graph.hpp"

namespace searcher {

    Graph::Graph(const matrix::Matrix& graphMatrix, const std::pair<uint32_t, uint32_t>& startLocation, const std::pair<uint32_t, uint32_t>& endLocation)
    : Searchable(GraphElement(startLocation, graphMatrix(startLocation.first, startLocation.second)), 
    GraphElement(endLocation, graphMatrix(endLocation.first, endLocation.second))), 
    m_graphMatrix(graphMatrix) {}

    std::vector<Element> Graph::getAllReachableElements(const Element& current) const {
        
    }

    Graph::GraphElement::GraphElement(const std::pair<uint32_t, uint32_t>& location, const double value)
    : m_location(location),
    m_value(value) {}

    double Graph::GraphElement::getValue() const {
        return m_value;
    }
}