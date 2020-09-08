#pragma once
#include "Searcher.hpp"
#include "string"

namespace searcher{

    class BFSSearcher : public Searcher{
         public:
            template <typename IdentifierType, typename ValueType>
            std::vector<std::string> search(const Searchable<IdentifierType, ValueType>& searchable) const;

        private:
            template <typename IdentifierType, typename ValueType>
            std::vector<std::string> recursiveSearch(const Searchable<IdentifierType, ValueType>& searchable, const Element<IdentifierType, ValueType>& elm, const Element<IdentifierType, ValueType>& target);
    };
}