#pragma once

#include "AbstractSearchable.hpp"
#include "Matrix.hpp"
#include "GraphElement.hpp"

#include <cstdint>
#include <utility>

namespace searcher
{

    /**
     * @brief This class represents a graph, which is defined by a matrix
     * 
     */
    class Graph : public AbstractSearchable<pair>
    {

        // the matrix which defines the structure of the graph
        const matrix::Matrix m_graphMatrix;

    public:
        /**
             * @brief Construct a new Graph object
             * 
             * @param graphMatrix the matrix which defines the graph
             * @param startPos the start position of the search
             * @param endPos the end position of the search
             */
        Graph(const matrix::Matrix &graphMatrix, const pair &startPos, const pair &endPos);

        /**
             * @brief Get the All Reachable Elements object of an element
             * 
             * @param current the given element
             * @return std::vector<std::shared_ptr<Element<pair>>> vector with all of the reachable elements of the given element 
             */
        std::vector<std::shared_ptr<Element<pair>>> getAllReachableElements(std::shared_ptr<Element<pair>> current) const override;

        /**
             * @brief Get the Direction between two elements in the searchable object, represented by a string
             * 
             * @param origin the origin element
             * @param destination the destination element
             * @return std::string a string that represents the direction from origin to destination.
             *      in this case, can be: left, right, up, down.
             */
        std::string getDirection(std::shared_ptr<Element<pair>> origin, std::shared_ptr<Element<pair>> destination) const override;

    protected:
        /**
             * @brief Check if an element is a valid element in the searchable
             * 
             * @param element the given element
             * @return true if the given element is a valid element
             * @return false if the given element is not a valid element
             */
        bool isValidElement(std::shared_ptr<Element<pair>> element) const override;
    };
}