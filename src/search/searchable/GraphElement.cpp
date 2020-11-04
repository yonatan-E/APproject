#include "GraphElement.hpp"

namespace searcher {

    GraphElement::GraphElement(const std::pair<uint32_t, uint32_t> &identifier, const double value)
        : m_identifier(identifier),
        m_value(value) {}

    void GraphElement::calculateHeuristics(std::shared_ptr<Element<pair>> startPos, std::shared_ptr<Element<pair>> endPos) {
        m_gScore = abs(getIdentifier().first - startPos->getIdentifier().first) + abs(getIdentifier().second - startPos->getIdentifier().second);
        m_hScore = abs(getIdentifier().first - endPos->getIdentifier().first) + abs(getIdentifier().second - endPos->getIdentifier().second);
    }

    const std::pair<uint32_t, uint32_t> &GraphElement::getIdentifier() const {
        return m_identifier;
    }

    double GraphElement::getValue() const {
        return m_value;
    }

    double GraphElement::getGScore() const {
        return m_gScore;
    }

    double GraphElement::getHScore() const {
        return m_hScore;
    }

    bool GraphElement::operator==(const Element<std::pair<uint32_t, uint32_t>> &other) const {
        return getIdentifier() == other.getIdentifier() && getValue() == other.getValue();
    }

    bool GraphElement::operator!=(const Element<std::pair<uint32_t, uint32_t>> &other) const {
            return !(*this == other);
    }
}