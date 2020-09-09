#pragma once

#include "Searchable.hpp"

namespace searcher {
    
    template <typename ElementType>
    class AbstractSearchable : public Searchable<ElementType> {

        const ElementType m_startElement;
        const ElementType m_endElement;

        public:
            AbstractSearchable(const ElementType& startElement, const ElementType& endElement);

            virtual ~AbstractSearchable() = default;

            virtual const ElementType& getStartElement() const final;

            virtual const ElementType& getEndElement() const final;

            virtual std::vector<ElementType> getAllReachableElements(const ElementType& current) const = 0;

           virtual  std::string direction(const ElementType& origin, const ElementType& destination) const = 0;
    };
}