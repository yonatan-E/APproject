#pragma once

#include <vector>

namespace searcher {

    template <typename IdentifierType, typename ValueType>
    class Element {

        const IdentifierType m_identifier;
        const ValueType m_value;

        public:

            Element(const IdentifierType& identifier, const ValueType& value);

            const IdentifierType& getIdentifier() const;

            const ValueType& getValue() const;
    };
}