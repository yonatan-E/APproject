#include "Searchable.hpp"

namespace searcher {

    template <typename IdentifierType, typename ValueType>
    Searchable<IdentifierType, ValueType>::Searchable(const Element<IdentifierType, ValueType>& startElement,
        const Element<IdentifierType, ValueType>& endElement)
    : m_startElement(startElement),
    m_endElement(endElement) {}

    template <typename IdentifierType, typename ValueType>
    const Element<IdentifierType, ValueType>& Searchable<IdentifierType, ValueType>::getStartElement() const {
        return m_startElement;
    }

    template <typename IdentifierType, typename ValueType>
    const Element<IdentifierType, ValueType>& Searchable<IdentifierType, ValueType>::getEndElement() const {
        return m_endElement;
    }
}