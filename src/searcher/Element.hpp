#pragma once

#include <vector>

namespace searcher {

    class Element {

        public:
            virtual double getValue() const = 0;
            virtual std::vector<Element> getReachables() const = 0;
    };
}