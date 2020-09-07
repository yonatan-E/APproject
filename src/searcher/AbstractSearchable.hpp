#pragma once

#include "Searchable.hpp"

namespace searcher {
    
    template <typename IdentifierType, typename ValueType>
    class AbstractSearchable : public Searchable<IdentifierType, ValueType> {

        const Element<IdentifierType, ValueType>& m_startElement;
        const Element<IdentifierType, ValueType>& m_endElement;

        public:
            AbstractSearchable(const Element<IdentifierType, ValueType>& startElement, const Element<IdentifierType, ValueType>& endElement);

            virtual ~AbstractSearchable() = default;

            virtual const Element<IdentifierType, ValueType>& getStartElement() const final;

            virtual const Element<IdentifierType, ValueType>& getEndElement() const final;

            virtual std::vector<Element<IdentifierType, ValueType>> getAllReachableElements(const Element<IdentifierType, ValueType>& current) const = 0;
    };
}