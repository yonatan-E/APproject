#pragma once

#include "Searchable.hpp"

namespace searcher {

    template <typename SearchResultType, typename Identifier>
    class Searcher {

        public:
        
            virtual SearchResultType search(const Searchable<Identifier>& searchable) const = 0;

            virtual ~Searcher() = default;
    };
}