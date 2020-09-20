#pragma once

namespace searcher {

    template <typename Identifier>
    class Element {

        Identifier m_identifier;
        double m_value;
        double m_gScore;
        double m_hScore;

        public:

            Element(const Identifier& identifier, const double value)
            : m_identifier(identifier),
            m_value(value) {}

            void calculateHeuristics(const Element<Identifier>& startPos, const Element<Identifier>& endPos);

            const Identifier& getIdentifier() const {
                return m_identifier;
            }

            double getValue() const {
                return m_value;
            }

            double getGScore() const {
                return m_gScore;
            }

            double getHScore() const {
                return m_hScore;
            }

            bool operator==(const Element<Identifier>& other) const {
                return m_identifier == other.m_identifier && m_value == other.m_value;
            }

            bool operator!=(const Element<Identifier>& other) const {
                return !(*this == other);
            }
    };

    template <typename Identifier>
    struct CompareByIdentifier {

        bool operator()(const Element<Identifier>& e1, const Element<Identifier>& e2) const {
            return e1.getIdentifier() < e2.getIdentifier();
        }
    };

    template <typename Identifier>
    struct CompareByHScore {

        bool operator()(const Element<Identifier>& e1, const Element<Identifier>& e2) const {
            return e1.getHScore() > e2.getHScore();
        }
    };

    template <typename Identifier>
    struct CompareByFScore {

        bool operator()(const Element<Identifier>& e1, const Element<Identifier>& e2) const {
            return e1.getGScore() + e1.getHScore() > e2.getGScore() + e2.getHScore();
        }
    };
}