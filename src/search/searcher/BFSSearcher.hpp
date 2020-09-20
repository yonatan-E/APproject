#pragma once

#include "AbstractSearcher.hpp"
#include <queue>

namespace searcher {

    template <typename Identifier>
    class BFSSearcher : public AbstractSearcher<Identifier> {

        // the queue which will be used for the BFS algorithm
        mutable std::queue<Element<Identifier>> queue;

        protected:

            void pushToContainer(const Element<Identifier>& element) const override {
                queue.push(element);
            }

            Element<Identifier> popFromContainer() const override {
                const Element<Identifier> popped = queue.front();
                queue.pop();
                return popped;
            }

            bool isContainerEmpty() const override {
                return queue.empty();
            }

            void clearContainer() const override {
                while(!queue.empty()) {
                    queue.pop();
                }
            }

            std::string getAlgorithmName() const override {
                return "BFS";
            }
    };
}