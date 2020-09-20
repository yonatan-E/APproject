#pragma once

#include "Searcher.hpp"
#include "SearchResult.hpp"
#include "SearchExceptions.hpp"
#include <set>
#include <map>

namespace searcher {

    template <typename Identifier>
    class AbstractSearcher : public Searcher<SearchResult, Identifier> {

        public:

            virtual SearchResult search(const Searchable<Identifier>& searchable) const {
                // clearing the container, to make sure it is empty
                clearContainer();

                // set of the visited elements
                std::set<Element<Identifier>, CompareByIdentifier<Identifier>> visited;

                // this map will hold for every element in the path, its previous element in the path.
                // the elements will be ordered in the map using the element Identifier comparator
                std::map<Element<Identifier>, Element<Identifier>, CompareByIdentifier<Identifier>> cameFrom;

                // marking the start element as visited
                visited.insert(searchable.getStartElement());
                // adding the start element to the container
                pushToContainer(searchable.getStartElement());

                while (!isContainerEmpty()) {
                    // popping an element from the container
                    const auto current = popFromContainer();

                    // in case that the popped element is the end element, then finishing the search
                    if (current == searchable.getEndElement()) {
                        break;
                    }

                    // else, getting all of the reachable elements of the popped element
                    for (auto& reachable : searchable.getAllReachableElements(current)) {
                        // if the reachable element has not been visited, then marking it as visited, 
                        // adding it to the container, and getting its previos element in the path
                        if (visited.find(reachable) == visited.end()) {
                            visited.insert(reachable);
                            pushToContainer(reachable);
                            cameFrom.emplace(reachable, current);         
                        }
                    }  
                }

                // if the end element has not been visited, then the path does not exist
                if (visited.find(searchable.getEndElement()) == visited.end()) {
                    throw exceptions::PathDoesNotExistException();
                }

                return this->reconstructPath(searchable, cameFrom);
            }

        protected:

            virtual SearchResult reconstructPath(
                const Searchable<Identifier>& searchable,
                std::map<Element<Identifier>, Element<Identifier>, CompareByIdentifier<Identifier>>& cameFrom) const {

                // this vector will hold the directions of the path from the start element to the end element
                std::vector<std::string> directions;

                // this variable will hold the total cost of the path. 
                // first, initializing it just with the cost of the start element
                auto pathCost = searchable.getStartElement().getValue();

                // iterating over the elements, and initializing the directions vector according to the path
                const auto *temp = &searchable.getEndElement();
                while (*temp != searchable.getStartElement()) {
                    // adding the cost of the current element to the total cost of the path
                    pathCost += temp->getValue();
                    // adding a direction between two elements in the path 
                    directions.insert(directions.begin(), searchable.getDirection(cameFrom.at(*temp), *temp));
                    // moving to the previous element
                    temp = &cameFrom.at(*temp);
                }

                return SearchResult(directions, pathCost, getAlgorithmName());
            }

            virtual void pushToContainer(const Element<Identifier>& element) const = 0;

            virtual Element<Identifier> popFromContainer() const = 0;

            virtual bool isContainerEmpty() const = 0;

            virtual void clearContainer() const = 0;

            virtual std::string getAlgorithmName() const = 0;

            virtual ~AbstractSearcher() = default;

    };
}