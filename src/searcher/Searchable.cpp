#include "Searchable.hpp"

namespace searcher {

    Searchable::Searchable(const Element& startElement, const Element& endElement)
    : m_startElement(startElement),
    m_endElement(endElement) {}

    const Element& Searchable::getStartElement() const {
        return m_startElement;
    }

    const Element& Searchable::getEndElement() const {
        return m_endElement;
    }
}