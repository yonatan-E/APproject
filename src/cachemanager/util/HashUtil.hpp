#pragma once

#include <string>
#include <cstdint>

namespace util {

    class HashUtil {

        public:

            static uint32_t calculateHash(const std::string& string);
    };
}