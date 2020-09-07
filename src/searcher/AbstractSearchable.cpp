#include "AbstractSearchable.hpp"

namespace searcher {

    template <typename IdentifierType, typename ValueType>
    AbstractSearchable<IdentifierType, ValueType>::AbstractSearchable(const Element<IdentifierType, ValueType>& startElement,
        const Element<IdentifierType, ValueType>& endElement)
    : m_startElement(startElement),
    m_endElement(endElement) {}

    template <typename IdentifierType, typename ValueType>
    const Element<IdentifierType, ValueType>& AbstractSearchable<IdentifierType, ValueType>::getStartElement() const {
        return m_startElement;
    }

    template <typename IdentifierType, typename ValueType>
    const Element<IdentifierType, ValueType>& AbstractSearchable<IdentifierType, ValueType>::getEndElement() const {
        return m_endElement;
    }
}