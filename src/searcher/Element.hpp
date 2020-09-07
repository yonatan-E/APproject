#pragma once

#include <vector>

namespace searcher {

    template <typename IdentifierType, typename ValueType>
    class Element {

        const IdentifierType m_identifier;
        const ValueType m_value;

        public:
            Element(const IdentifierType& identifier, const ValueType& value);
            virtual const IdentifierType& getIdentifier() const final;
            virtual const ValueType& getValue() const final;
    };
}