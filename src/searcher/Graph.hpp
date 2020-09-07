#pragma once

#include "Searchable.hpp"
#include "Matrix.hpp"
#include <cstdint>
#include <utility>

namespace searcher {

    class Graph : public Searchable {

        const matrix::Matrix m_graphMatrix;

        public:
            Graph(const matrix::Matrix& graphMatrix, const std::pair<uint32_t, uint32_t>& startLocation, const std::pair<uint32_t, uint32_t>& endLocation);
            std::vector<Element> getAllReachableElements(const Element& current) const override;

            class GraphElement : public Element {

                const std::pair<uint32_t, uint32_t> m_location;
                const double m_value;

                public:
                    GraphElement(const std::pair<uint32_t, uint32_t>& location, const double value);
                    virtual double getValue() const override;
            };
    };
}