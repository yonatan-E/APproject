#include "SerialServer.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>

namespace server{

    const uint32_t m_backlog = 20;

     void SerialServer::open(uint32_t serverPort, const clientside::SolverClientHandler<searcher::Graph, searcher::SearchResult>& clientHandler) const{
       
       sockaddr_in clientAddress{};
       sockaddr_in serverAddress{};

        const auto serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket < 0) {
            //error
        }

        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = serverPort;

        auto bindResult = bind(serverSocket, reinterpret_cast<const sockaddr *>(&serverAddress), sizeof(serverAddress));
        if (bindResult < 0) {
            //error
        }

        auto listenResult = listen(serverSocket, m_backlog);
        if (listenResult < 0) {
            //error
        }

        while(!stop()){
            //waiting for connections

            uint32_t addrSize = sizeof(clientAddress);

            const auto clientSocket = accept(serverSocket, reinterpret_cast<sockaddr *>(&clientAddress)
            , reinterpret_cast<socklen_t*>(&addrSize));

            if(clientSocket < 0){
                //error
            }
  
            clientHandler.handleClient(clientSocket);
        }
    }

    bool SerialServer::stop() const{
        return false;
    }

}