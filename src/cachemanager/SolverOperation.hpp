#pragma once

#include "Operation.hpp"

namespace operation {

    class SolverOperation : public Operation {

        public:

            SolverOperation(const uint32_t hashCode, const std::string& result);

            void writeOperationToFile(const std::string& filePath) const override;

        private:

            const std::string m_result;
    };
}