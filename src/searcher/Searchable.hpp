#pragma once

#include "Element.hpp"
#include <vector>

namespace searcher {

    class Searchable {
        
        public:
            virtual Element getStartElement() const = 0;
            virtual Element getGoalElement() const = 0;
            virtual std::vector<Element> getAllReachableElements(const Element& current) const final;
    };
}