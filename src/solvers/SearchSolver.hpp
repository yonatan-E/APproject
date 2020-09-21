#pragma once

#include "Solver.hpp"
#include "ServerExceptions.hpp"
#include "../search/searcher/Searcher.hpp"
#include "../search/searchable/Searchable.hpp"
#include "../search/searchable/Graph.hpp"
#include <cstdint>

namespace solver {

    class SearchSolver : public Solver<searcher::Graph, searcher::SearchResult> {

        const searcher::Searcher<searcher::SearchResult, pair>& m_searcher;

        public:

            SearchSolver(const searcher::Searcher<searcher::SearchResult, pair>& searcher)
            : m_searcher(searcher) {}

            searcher::SearchResult solve(const Graph& problem) const override {
                return m_searcher.search(problem);
            }

            Graph parseInput(const std::string& input) const override {
                // getting the first line
                std::string firstLine(&input[0], &input[input.find("\r\n", 0)]);
                firstLine.erase(std::remove(line.begin(), line.end(), ' '), line.end());
                // getting the number of the rows and the columns of the matrix
                uint32_t numRows;
                uint32_t numColumns;
                try {
                    numRows = std::stoi(std::string(&firstLine[0], &input[input.find(",", 0)]));
                    numColumns = std::stoi(std::string(&input[input.find(",", 0) + 1], &input[firstLine.size()]));
                } catch (...) {
                    // throwing a file format exception in case that the stoi function hasn't succeeded
                    throw server::exceptions::MessageFormatException();
                }

                // throwing an exception in a case that the matrix height or width is 0
                if (numRows == 0 || numColumns == 0) {
                    throw server::exceptions::MessageFormatException();
                }

                // creating a new matrix with sizes numRows * numColumns
                matrix::Matrix matrix(numRows, numColumns);
                // reading from the file and filling the matrix
                size_t it = input.find("\r\n", 0) + 2;
                for (uint32_t i = 0; i < numRows; ++i) {
                    std::string line(&input[it], &input[input.find("\r\n", it)]);
                    // removing the spaces from the line string
                    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
                    // j will run on the string line, colIndex will run on the matrix columns
                    uint32_t j = 0, colIndex = 0;
                    // iterating over the line string and initializing the matrix
                    while (j < line.size()) {
                        size_t k = line.find(',', j);
                        // if k == npos, it means that there aren't more ',' in the line, so the current number
                        // is the last number in the line
                        if (k == std::string::npos) {
                            k = line.size();
                        }
                        // getting the specified value
                        double val;
                        if (line.substr(j, k - j + 1) == "b") {
                            val = 0;
                        } else {
                            try {
                                val = std::stoi(line.substr(j, k - j + 1));
                            } catch (...) {
                                // throwing a file format exception in case that the stoi function hasn't succeeded
                                throw server::exceptions::MessageFormatException();
                            }
                        }
                        // throwing an exception in case that the specified value in the matrix is smaller than 1
                        if (val < 1) {
                            throw server::exceptions::MessageFormatException();
                        }
                        // finally setting the value in the matrix
                        matrix.setAt(i, colIndex, val);

                        // promoting the iterators
                        j = k + 1;
                        colIndex++;
                    }

                    it = input.find("\r\n", it) + 2;
                }

                // getting the current line
                std::string currentLine(&input[it], &input[input.find("\r\n", it)]);
                firstLine.erase(std::remove(line.begin(), line.end(), ' '), line.end());
                // getting the start position
                pair startPos;
                try {
                    startPos.first = std::stoi(std::string(&firstLine[it], &input[input.find(",", it)]));
                    startPos.second = std::stoi(std::string(&input[input.find(",", it) + 1], &input[firstLine.size()]));
                } catch (...) {
                    // throwing a file format exception in case that the stoi function hasn't succeeded
                    throw server::exceptions::MessageFormatException();
                }
                it = input.find("\r\n", it) + 2;

                // getting the current line
                currentLine = std::string(&input[it], &input[input.find("\r\n", it)]);
                firstLine.erase(std::remove(line.begin(), line.end(), ' '), line.end());
                // getting the start position
                pair endPos;
                try {
                    endPos.first = std::stoi(std::string(&firstLine[it], &input[input.find(",", it)]));
                    endPos.second = std::stoi(std::string(&input[input.find(",", it) + 1], &input[firstLine.size()]));
                } catch (...) {
                    // throwing a file format exception in case that the stoi function hasn't succeeded
                    throw server::exceptions::MessageFormatException();
                }

                return Graph(matrix, startPos, endPos);
            }
    };
}