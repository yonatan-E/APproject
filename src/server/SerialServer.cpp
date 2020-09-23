#include "SerialServer.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>

namespace server_side {

     const uint32_t m_backlog = 20;

     void SerialServer::open(const uint32_t serverPort, const client_side::ClientHandler& clientHandler) const{
       
        struct sockaddr_in clientAddress;
        struct sockaddr_in serverAddress;

        const uint32_t serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket < 0) {
            //error
        }

        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(serverPort);

        const uint32_t bindResult = bind(serverSocket, reinterpret_cast<struct sockaddr *>(&serverAddress), sizeof(serverAddress));
        if (bindResult < 0) {
            //error
        }

        const uint32_t listenResult = listen(serverSocket, m_backlog);
        if (listenResult < 0) {
            //error
        }

        while(!stop()){

            //waiting for connections

            uint32_t addrSize = sizeof(clientAddress);

            const uint32_t clientSocket = accept(serverSocket, reinterpret_cast<struct sockaddr *>(&clientAddress)
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