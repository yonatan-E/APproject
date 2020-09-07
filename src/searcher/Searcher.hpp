#pragma once

#include "Searchable.hpp"
#include <string>

namespace searcher {

    class Searcher {

        public:
            virtual std::vector<std::string> search(const Searchable& searchable) const;
    };
}