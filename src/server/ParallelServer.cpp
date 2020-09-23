#include "ParallelServer.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <pthread>

namespace server{

    void ParallelServer::open(const uint32_t serverPort, const clientside::ClientHandler& clientHandler) const{
      
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

            const auto clientSocket = accept(serverSocket, reinterpret_cast<sockaddr *>(&clientAddress)
            , reinterpret_cast<socklen_t*>(&addrSize));

            if(clientSocket < 0){
                //error
            }
  
            clientHandler.handleClient(clientSocket);

            pthred_t t;
            pthread_create(&t, nullptr,  handleConnection, &clientSocket);
        }
  
    }

    void* handleConnection(int* clientSocketPointer){
        clientHandler.handleClient(*clientSocketPointer);
    }

    bool ParallelServer::stop() const{
        return false;
    }

}