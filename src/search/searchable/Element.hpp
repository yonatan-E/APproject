#pragma once

#include <memory>

namespace searcher
{

    /**
     * @brief This class represents an element of a searchable object
     * 
     * @tparam Identifier the identifier of an element
     */
    template <typename Identifier>
    class Element
    {

    public:

        /**
             * @brief Calculate and set the heuristic scores of the graph element
             * 
             * @param startPos the start position of the search
             * @param endPos the end position of the search
             */
        virtual void calculateHeuristics(const std::shared_ptr<Element<Identifier>> &startPos, const std::shared_ptr<Element<Identifier>> &endPos) = 0;

        /**
             * @brief Get the Identifier of the element
             * 
             * @return const Identifier& the identifier of the element
             */
        virtual const Identifier &getIdentifier() const = 0;

        /**
             * @brief Get the Value of the element
             * 
             * @return double the value of the element
             */
        virtual double getValue() const = 0;

        /**
             * @brief Get the heuristic G score of the element
             * 
             * @return double the G score of the element, which is the estimated distance to the end position
             */
        virtual double getGScore() const = 0;

        /**
             * @brief Get the heuristic H score of the element
             * 
             * @return double the H score of the element, which is the distance to the start position
             */
        virtual double getHScore() const = 0;

        /**
             * @brief Compare operator
             * 
             * @param other the compared object
             * @return true if the elements are equal
             * @return false if the elements are not equal
             */
        virtual bool operator==(const Element<Identifier> &other) const = 0;

        /**
             * @brief Negative compare operator
             * 
             * @param other the compared object
             * @return true if the elements are not equal
             * @return false if the elements are equal
             */
        virtual bool operator!=(const Element<Identifier> &other) const = 0;
    };

    /**
     * @brief This function object compares two elements by their identifier
     * 
     * @tparam Identifier the identifier of an element
     */
    template <typename Identifier>
    struct CompareByIdentifier
    {

        /**
         * @brief Compare between two elements by their identifier
         * 
         * @param e1 the fiest element
         * @param e2 the second element
         * @return true if e1 is smaller
         * @return false if e2 is smaller
         */
        bool operator()(const std::shared_ptr<Element<Identifier>> &e1, const std::shared_ptr<Element<Identifier>> &e2) const
        {
            return e1->getIdentifier() < e2->getIdentifier();
        }
    };

    /**
     * @brief This function object compares two elements by their H score
     * 
     * @tparam Identifier the identifier of an element
     */
    template <typename Identifier>
    struct CompareByHScore
    {

        /**
         * @brief Compare between two elements by their H score
         * 
         * @param e1 the fiest element
         * @param e2 the second element
         * @return true if e1 is smaller
         * @return false if e2 is smaller
         */
        bool operator()(const std::shared_ptr<Element<Identifier>> &e1, const std::shared_ptr<Element<Identifier>> &e2) const
        {
            return e1->getHScore() > e2->getHScore();
        }
    };

    /**
     * @brief This function object compares two elements by their F score, which is the sum of the G score and the H score
     * 
     * @tparam Identifier the identifier of an element
     */
    template <typename Identifier>
    struct CompareByFScore
    {

        /**
         * @brief Compare between two elements by their F score
         * 
         * @param e1 the fiest element
         * @param e2 the second element
         * @return true if e1 is smaller
         * @return false if e2 is smaller
         */
        bool operator()(const std::shared_ptr<Element<Identifier>> &e1, const std::shared_ptr<Element<Identifier>> &e2) const
        {
            return e1->getGScore() + e1->getHScore() > e2->getGScore() + e2->getHScore();
        }
    };
}