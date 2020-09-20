#pragma once

#include "Element.hpp"
#include <vector>
#include <string>

namespace searcher {
    
    template <typename Identifier>
    class Searchable {

        public:

            virtual const Element<Identifier>& getStartElement() const = 0;

            virtual const Element<Identifier>& getEndElement() const = 0;

            virtual std::vector<Element<Identifier>> getAllReachableElements(const Element<Identifier>& current) const = 0;

            virtual std::string getDirection(const Element<Identifier>& origin, const Element<Identifier>& destination) const = 0;

            virtual ~Searchable() = default;
    };
}