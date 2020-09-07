#pragma once

#include "Element.hpp"
#include <vector>

namespace searcher {
    
    template <typename IdentifierType, typename ValueType>
    class Searchable {

        public:

            virtual const Element<IdentifierType, ValueType>& getStartElement() const = 0;

            virtual const Element<IdentifierType, ValueType>& getEndElement() const = 0;

            virtual std::vector<Element<IdentifierType, ValueType>> getAllReachableElements(const Element<IdentifierType, ValueType>& current) const = 0;
    };
}