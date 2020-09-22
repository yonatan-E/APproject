#pragma once

#include "AbstractSearchable.hpp"
#include "matrix/Matrix.hpp"
#include "Element.hpp"
#include <cstdint>
#include <utility>

namespace searcher {

    typedef std::pair<uint32_t, uint32_t> pair;
    typedef Element<pair> graphElement;

    class Graph : public AbstractSearchable<pair> {

        const matrix::Matrix m_graphMatrix;

        public:

            Graph(const matrix::Matrix& graphMatrix, const pair& startPos, const pair& endPos);
            
            std::vector<graphElement> getAllReachableElements(const graphElement& current) const override;

            std::string getDirection(const graphElement& origin, const graphElement& destination) const override;

            bool isValidElement(const graphElement& element) const override;
    };
}