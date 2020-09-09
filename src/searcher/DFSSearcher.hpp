#pragma once
#include "Searcher.hpp"
#include "string"

namespace searcher{

    class DFSSearcher : public Searcher {

        public:
            template <typename ElementType>
            std::vector<std::string> search(const Searchable<ElementType>& searchable) const;

        private:
            template <typename ElementType>
            std::vector<std::string> recursiveSearch(std::vector<ElementType>& visited, std::vector<std::string>& directions, const Searchable<ElementType>& searchable, const ElementType& elm);
    };
}