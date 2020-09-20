#pragma once

#include "AbstractSearcher.hpp"
#include <queue>

namespace searcher {

    template <typename Identifier>
    class BestFSSearcher : public AbstractSearcher<Identifier> {

        // the proirity queue which will be used for the BestFS algorithm.
        // the best element in the priority queue will be the element which its H Score is the best.
        // so, the elements in the priority queue will be ordered using the element H Score comparator
        mutable std::priority_queue<Element<Identifier>, std::vector<Element<Identifier>>, CompareByHScore<Identifier>> pqueue;

        protected:

            void pushToContainer(const Element<Identifier>& element) const override {
                pqueue.push(element);
            }

            Element<Identifier> popFromContainer() const override {
                const Element<Identifier> popped = pqueue.top();
                pqueue.pop();
                return popped;
            }

            bool isContainerEmpty() const override {
                return pqueue.empty();
            }

            void clearContainer() const override {
                while(!pqueue.empty()) {
                    pqueue.pop();
                }
            }

            std::string getAlgorithmName() const override {
                return "BestFS";
            }
    };
}