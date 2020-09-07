#include "Searchable.hpp"

namespace searcher {

    std::vector<Element> Searchable::getAllReachableElements(const Element& current) const {
        return current.getReachables();
    }
}