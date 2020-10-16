#pragma once

#include "Server.hpp"

#include <unordered_map>
#include <functional>
#include <memory>

namespace server_side {

    class ServerFactory {

        std::unordered_map<std::string, std::function<std::unique_ptr<Server>()>> m_map;

        public:

            ServerFactory();

            std::unique_ptr<Server> getServer(const std::string& type) const;

            std::unique_ptr<Server> getDefaultServer() const;
    };
}