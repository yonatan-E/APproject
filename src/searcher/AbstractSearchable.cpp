#include "AbstractSearchable.hpp"

namespace searcher {

    template <typename ElementType>
    AbstractSearchable<ElementType>::AbstractSearchable(const ElementType& startElement,
        const ElementType& endElement)
    : m_startElement(startElement),
    m_endElement(endElement) {}

    template <typename ElementType>
    const ElementType& AbstractSearchable<ElementType>::getStartElement() const {
        return m_startElement;
    }

    template <typename ElementType>
    const ElementType& AbstractSearchable<ElementType>::getEndElement() const {
        return m_endElement;
    }
}