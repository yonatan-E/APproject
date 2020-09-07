#pragma once

#include "Element.hpp"
#include <vector>

namespace searcher {

    class Searchable {

        const Element& m_startElement;
        const Element& m_endElement;

        public:
            Searchable(const Element& startElement, const Element& endElement);
            virtual const Element& getStartElement() const final;
            virtual const Element& getEndElement() const final;
            virtual std::vector<Element> getAllReachableElements(const Element& current) const final;
            virtual ~Searchable() = default;
    };
}