#pragma once

#include "Searchable.hpp"
#include "SearchExceptions.hpp"

namespace searcher
{

    /**
     * @brief This class is a base class for some searchable object classes
     * 
     * @tparam Identifier the identifier of an element in the searchable object
     */
    template <typename Identifier>
    class AbstractSearchable : public Searchable<Identifier>
    {

        // the start position of the search
        const Element<Identifier> m_startPos;
        // the end position of the search
        const Element<Identifier> m_endPos;

    public:
        /**
             * @brief Construct a new Abstract Searchable object
             * 
             * @param startPos the start position
             * @param endPos the end position
             */
        AbstractSearchable(const Element<Identifier> &startPos, const Element<Identifier> &endPos)
            : m_startPos(startPos), m_endPos(endPos)
        {
            // checking if the start position is valid
            if (!isValidElement(startPos))
            {
                throw exceptions::InvalidPositionException("The given start position is invalid");
            }

            // checking if the end position is valid
            if (!isValidElement(endPos))
            {
                throw exceptions::InvalidPositionException("The given end position is invalid");
            }
        }

        /**
             * @brief Get the Start Element of the search
             * 
             * @return const Element<Identifier>& the element where the search starts
             */
        virtual const Element<Identifier> &getStartElement() const final
        {
            return m_startPos;
        }

        /**
             * @brief Get the End Element of the search
             * 
             * @return const Element<Identifier>& the element where the search end
             */
        virtual const Element<Identifier> &getEndElement() const final
        {
            return m_endPos;
        }

        /**
             * @brief Get the All Reachable Elements object of an element
             * 
             * @param current the given element
             * @return std::vector<Element<Identifier>> vector with all of the reachable elements of the given element 
             */
        virtual std::vector<Element<Identifier>> getAllReachableElements(const Element<Identifier> &current) const = 0;

        /**
             * @brief Get the Direction between two elements in the searchable object, represented by a string
             * 
             * @param origin the origin element
             * @param destination the destination element
             * @return std::string a string that represents the direction from origin to destination
             */
        virtual std::string getDirection(const Element<Identifier> &origin, const Element<Identifier> &destination) const = 0;

        /**
             * @brief Virtual destructor
             * 
             */
        virtual ~AbstractSearchable() = default;

    protected:
        /**
             * @brief Check if an element is a valid element in the searchable
             * 
             * @param element the given element
             * @return true if the given element is a valid element
             * @return false if the given element is not a valid element
             */
        virtual bool isValidElement(const Element<Identifier> &element) const
        {
            if (element.getGScore(); < 1) {
                return true;
            }
            // the default implementation will guess that the given element is always valid
             if(element.getGScore() < 1){
                return true;
            }
            return true;
        }
    };
}