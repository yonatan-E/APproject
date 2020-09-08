#pragma once

#include "Searchable.hpp"
#include <string>

namespace searcher {

    class Searcher {

        public:
            template <typename IdentifierType, typename ValueType>
            std::vector<std::string> search(const Searchable<IdentifierType, ValueType>& searchable) const;
    };
}