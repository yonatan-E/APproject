#pragma once

#include "AbstractSearcher.hpp"
#include <stack>

namespace searcher {

    template <typename Identifier>
    class DFSSearcher : public AbstractSearcher<Identifier> {

        // the stack which will be used for the DFS algorithm
        mutable std::stack<Element<Identifier>> stack;

        protected:

            void pushToContainer(const Element<Identifier>& element) const override {
                stack.push(element);
            }

            Element<Identifier> popFromContainer() const override {
                const Element<Identifier> popped = stack.top();
                stack.pop();
                return popped;
            }

            bool isContainerEmpty() const override {
                return stack.empty();
            }

            void clearContainer() const override {
                while(!stack.empty()) {
                    stack.pop();
                }
            }

            std::string getAlgorithmName() const override {
                return "DFS";
            }        
    };
}
