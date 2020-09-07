#include "Element.hpp"

namespace searcher {

    template <typename IdentifierType, typename ValueType>
    Element<IdentifierType, ValueType>::Element(const IdentifierType& identifier, const ValueType& value)
    : Element<IdentifierType, ValueType>::m_identifier(identifier), 
    Element<IdentifierType, ValueType>::m_value(value) {}

    template <typename IdentifierType, typename ValueType>
    const IdentifierType& Element<IdentifierType, ValueType>::getIdentifier() const {
        return m_identifier;
    }

    template <typename IdentifierType, typename ValueType>
    const ValueType& Element<IdentifierType, ValueType>::getValue() const {
        return m_value;
    }
}