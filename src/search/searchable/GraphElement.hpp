#pragma once

#include "Element.hpp"

#include <utility>
#include <cstdint>

namespace searcher {

    typedef std::pair<uint32_t, uint32_t> pair;

    class GraphElement : public Element<pair> {

        pair m_identifier;
        double m_value;
        double m_gScore;
        double m_hScore;

        public:
            /**
             * @brief Construct a new Graph Element object
             * 
             * @param identifier the identifier of the element
             * @param value the value of the element
             */
            GraphElement(const pair &identifier, double value);

            /**
             * @brief Calculate and set the heuristic scores of the graph element
             * 
             * @param startPos the start position of the search
             * @param endPos the end position of the search
             */
            void calculateHeuristics(const std::shared_ptr<Element<pair>> &startPos, const std::shared_ptr<Element<pair>> &endPos) override;

            /**
             * @brief Get the Identifier of the element
             * 
             * @return const Identifier& the identifier of the element
             */
            const pair &getIdentifier() const override;

            /**
             * @brief Get the Value of the element
             * 
             * @return double the value of the element
             */
            double getValue() const override;

            /**
             * @brief Get the heuristic G score of the element
             * 
             * @return double the G score of the element, which is the estimated distance to the end position
             */
            double getGScore() const override;

            /**
                 * @brief Get the heuristic H score of the element
                 * 
                 * @return double the H score of the element, which is the distance to the start position
                 */
            double getHScore() const override;

            /**
             * @brief Compare operator
             * 
             * @param other the compared object
             * @return true if the elements are equal
             * @return false if the elements are not equal
             */
            bool operator==(const Element<pair> &other) const override;

            /**
             * @brief Negative compare operator
             * 
             * @param other the compared object
             * @return true if the elements are not equal
             * @return false if the elements are equal
             */
            bool operator!=(const Element<pair> &other) const override;
    };
}