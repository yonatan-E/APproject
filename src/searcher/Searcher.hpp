#pragma once

#include "Searchable.hpp"
#include <string>

namespace searcher {

    class Searcher {

        public:
            template <typename ElementType>
            std::vector<std::string> search(const Searchable<ElementType>& searchable) const;
    };
}