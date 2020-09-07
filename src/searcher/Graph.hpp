#pragma once

#include "AbstractSearchable.hpp"
#include "Matrix.hpp"
#include <cstdint>
#include <utility>

namespace searcher {

    typedef std::pair<uint32_t, uint32_t> pair;
    typedef Element<std::pair<uint32_t, uint32_t>, double> graphElement;

    class Graph : public AbstractSearchable<pair, double> {

        const matrix::Matrix m_graphMatrix;

        public:

            Graph(const matrix::Matrix& graphMatrix, const pair& startLocation, const pair& endLocation);
            std::vector<graphElement> getAllReachableElements(const graphElement& current) const override;
    };
}