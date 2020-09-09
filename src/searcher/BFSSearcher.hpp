#pragma once
#include "Searcher.hpp"
#include "string"

namespace searcher{

    class BFSSearcher : public Searcher {

        public:
            template <typename ElementType>
            std::vector<std::string> search(const Searchable<ElementType>& searchable) const;

        private:
            template <typename ElementType>
            std::vector<std::string> recursiveSearch(const Searchable<ElementType>& searchable, const ElementType& elm, const ElementType& target);
    };
}