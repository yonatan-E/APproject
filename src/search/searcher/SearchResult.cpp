#include "SearchResult.hpp"

namespace searcher
{

    SearchResult::SearchResult(const std::vector<std::string> &directions, const double cost, const std::string &algorithmName)
        : m_directions(directions),
          m_cost(cost),
          m_algorithmName(algorithmName) {}

    std::string SearchResult::toString() const
    {

        std::string stringRepresentation = std::to_string(m_cost) + "," + m_algorithmName;

        for (size_t i = 0; i < m_directions.size(); i++)
        {
            stringRepresentation += "," + m_directions[i];
        }

        return stringRepresentation;
    }
}