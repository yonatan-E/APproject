#pragma once

#include <vector>
#include <string>

namespace searcher {

    /**
     * @brief This class represents a specific search result of a pathfinding search.
     * 
     */
    class SearchResult {
        
        // a vector with the directions of the path
        const std::vector<std::string> m_directions;
        // the total cost of the path
        const double m_cost;
        // the name of the algorithm used for the search
        const std::string m_algorithmName;

        public:

            /**
             * @brief Construct a new Search Result object
             * 
             * @param directions the directions vector of the search
             * @param cost the total cost of the search
             * @param algorithmName the name of the algorithm used for the search
             */
            SearchResult(const std::vector<std::string>& directions, const double cost, const std::string& algorithmName);

            /**
             * @brief Convert the search result to a string
             * 
             * @return std::string a string represents the search result
             */
            std::string toString() const;  
    };
}