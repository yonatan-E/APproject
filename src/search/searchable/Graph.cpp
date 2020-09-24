#include "Graph.hpp"

namespace searcher
{

    Graph::Graph(const matrix::Matrix &graphMatrix, const pair &startPos, const pair &endPos)
        : AbstractSearchable(graphElement(startPos, graphMatrix(startPos.first, startPos.second)),
                             graphElement(endPos, graphMatrix(endPos.first, endPos.second))),
          m_graphMatrix(graphMatrix) {}

    std::vector<graphElement> Graph::getAllReachableElements(const graphElement &current) const
    {
        // this vector will contain the elements which can be reached from the current element
        std::vector<graphElement> reachables;

        // getting the exact location of the current element
        const auto rowIdx = current.getIdentifier().first;
        const auto colIdx = current.getIdentifier().second;

        // adding the element in the left of the current element, if exists
        if (colIdx > 0)
        {
            // checking if the element in the left actually exists
            if (m_graphMatrix(rowIdx, colIdx - 1) != 0)
            {
                // creating the left element and calculating its heuristics
                graphElement left(pair(rowIdx, colIdx - 1), m_graphMatrix(rowIdx, colIdx - 1));
                left.calculateHeuristics(getStartElement(), getEndElement());
                reachables.push_back(left);
            }
        }

        // adding the element in the right of the current element, if exists
        if (colIdx < m_graphMatrix.getWidth() - 1)
        {
            // checking if the element in the right actually exists
            if (m_graphMatrix(rowIdx, colIdx + 1) != 0)
            {
                // creating the right element and calculating its heuristics
                graphElement right(pair(rowIdx, colIdx + 1), m_graphMatrix(rowIdx, colIdx + 1));
                right.calculateHeuristics(getStartElement(), getEndElement());
                reachables.push_back(right);
            }
        }

        // adding the element above the current element, if exists
        if (rowIdx > 0)
        {
            // checking if the element above actually exists
            if (m_graphMatrix(rowIdx - 1, colIdx) != 0)
            {
                // creating the element above and calculating its heuristics
                graphElement up(pair(rowIdx - 1, colIdx), m_graphMatrix(rowIdx - 1, colIdx));
                up.calculateHeuristics(getStartElement(), getEndElement());
                reachables.push_back(up);
            }
        }

        // adding the element below the current element, if exists
        if (rowIdx < m_graphMatrix.getHeight() - 1)
        {
            // checking if the element below actually exists
            if (m_graphMatrix(rowIdx + 1, colIdx) != 0)
            {
                graphElement down(pair(rowIdx + 1, colIdx), m_graphMatrix(rowIdx + 1, colIdx));
                down.calculateHeuristics(getStartElement(), getEndElement());
                reachables.push_back(down);
            }
        }

        return reachables;
    }

    std::string Graph::getDirection(const graphElement &origin, const graphElement &destination) const
    {
        if (origin.getIdentifier().second == destination.getIdentifier().second + 1 && origin.getIdentifier().first == destination.getIdentifier().first)
        {
            return "Left";
        }
        else if (origin.getIdentifier().second == destination.getIdentifier().second - 1 && origin.getIdentifier().first == destination.getIdentifier().first)
        {
            return "Right";
        }
        else if (origin.getIdentifier().second == destination.getIdentifier().second && origin.getIdentifier().first == destination.getIdentifier().first + 1)
        {
            return "Up";
        }
        else if (origin.getIdentifier().second == destination.getIdentifier().second && origin.getIdentifier().first == destination.getIdentifier().first - 1)
        {
            return "Down";
        }
        return "";
    }

    bool Graph::isValidElement(const graphElement &element) const
    {
        return element.getIdentifier().first < m_graphMatrix.getHeight() && element.getIdentifier().second < m_graphMatrix.getWidth() && m_graphMatrix(element.getIdentifier().first, element.getIdentifier().second) > 0;
    }
}