#pragma once

#include <vector>

namespace searcher {

    class Element {

        public:
            virtual double getValue() const = 0;
    };
}