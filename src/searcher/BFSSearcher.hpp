#pragma once
#include "Searcher.hpp"

namespace searcher{

    class BFSSearcher : public Searcher{
         public:
            template <typename IdentifierType, typename ValueType>
            std::vector<std::string> search(const Searchable<IdentifierType, ValueType>& searchable) const;
    };
}