#pragma once

namespace searcher {

    /**
     * @brief This class represents an element of a searchable object
     * 
     * @tparam Identifier the identifier of an element
     */
    template <typename Identifier>
    class Element {

        Identifier m_identifier;
        double m_value;
        double m_gScore;
        double m_hScore;

        public:

            /**
             * @brief Construct a new Element object
             * 
             * @param identifier the identifier of the element
             * @param value the value of the element
             */
            Element(const Identifier& identifier, const double value)
            : m_identifier(identifier),
            m_value(value) {}

            /**
             * @brief Calculate and set the heuristic scores of the element
             * 
             * @param startPos the start position of the search
             * @param endPos the end position of the search
             */
            void calculateHeuristics(const Element<Identifier>& startPos, const Element<Identifier>& endPos);

            /**
             * @brief Get the Identifier of the element
             * 
             * @return const Identifier& the identifier of the element
             */
            const Identifier& getIdentifier() const {
                return m_identifier;
            }
            
            /**
             * @brief Get the Value of the element
             * 
             * @return double the value of the element
             */
            double getValue() const {
                return m_value;
            }

            /**
             * @brief Get the heuristic G score of the element
             * 
             * @return double the G score of the element, which is the estimated distance to the end position
             */
            double getGScore() const {
                return m_gScore;
            }

            /**
             * @brief Get the heuristic H score of the element
             * 
             * @return double the H score of the element, which is the distance to the start position
             */
            double getHScore() const {
                return m_hScore;
            }

            /**
             * @brief Compare operator
             * 
             * @param other the compared object
             * @return true if the elements are equal
             * @return false if the elements are not equal
             */
            bool operator==(const Element<Identifier>& other) const {
                return m_identifier == other.m_identifier && m_value == other.m_value;
            }

            /**
             * @brief Negative compare operator
             * 
             * @param other the compared object
             * @return true if the elements are not equal
             * @return false if the elements are equal
             */
            bool operator!=(const Element<Identifier>& other) const {
                return !(*this == other);
            }
    };

    /**
     * @brief This function object compares two elements by their identifier
     * 
     * @tparam Identifier the identifier of an element
     */
    template <typename Identifier>
    struct CompareByIdentifier {

        /**
         * @brief Compare between two elements by their identifier
         * 
         * @param e1 the fiest element
         * @param e2 the second element
         * @return true if e1 is smaller
         * @return false if e2 is smaller
         */
        bool operator()(const Element<Identifier>& e1, const Element<Identifier>& e2) const {
            return e1.getIdentifier() < e2.getIdentifier();
        }
    };


    /**
     * @brief This function object compares two elements by their H score
     * 
     * @tparam Identifier the identifier of an element
     */
    template <typename Identifier>
    struct CompareByHScore {

        /**
         * @brief Compare between two elements by their H score
         * 
         * @param e1 the fiest element
         * @param e2 the second element
         * @return true if e1 is smaller
         * @return false if e2 is smaller
         */
        bool operator()(const Element<Identifier>& e1, const Element<Identifier>& e2) const {
            return e1.getHScore() > e2.getHScore();
        }
    };

    /**
     * @brief This function object compares two elements by their F score, which is the sum of the G score and the H score
     * 
     * @tparam Identifier the identifier of an element
     */
    template <typename Identifier>
    struct CompareByFScore {

        /**
         * @brief Compare between two elements by their F score
         * 
         * @param e1 the fiest element
         * @param e2 the second element
         * @return true if e1 is smaller
         * @return false if e2 is smaller
         */
        bool operator()(const Element<Identifier>& e1, const Element<Identifier>& e2) const {
            return e1.getGScore() + e1.getHScore() > e2.getGScore() + e2.getHScore();
        }
    };
}