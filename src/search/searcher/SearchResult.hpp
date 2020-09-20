#pragma once

#include <vector>
#include <string>

namespace searcher {

    class SearchResult {

        const std::vector<std::string> m_directions;
        const double m_cost;
        const std::string m_algorithmName;

        public:

            SearchResult(const std::vector<std::string>& directions, const double cost, const std::string& algorithmName);

            std::string toString() const;  
    };
}