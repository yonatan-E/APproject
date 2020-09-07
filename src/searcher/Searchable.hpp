#pragma once

#include "Element.hpp"
#include <vector>

namespace searcher {
    
    template <typename IdentifierType, typename ValueType>
    class Searchable {

        const Element<IdentifierType, ValueType>& m_startElement;
        const Element<IdentifierType, ValueType>& m_endElement;

        public:
            Searchable(const Element<IdentifierType, ValueType>& startElement, const Element<IdentifierType, ValueType>& endElement);
            virtual ~Searchable() = default;
            virtual const Element<IdentifierType, ValueType>& getStartElement() const final;
            virtual const Element<IdentifierType, ValueType>& getEndElement() const final;
            virtual std::vector<Element<IdentifierType, ValueType>> getAllReachableElements(const Element<IdentifierType, ValueType>& current) const = 0;
    };
}