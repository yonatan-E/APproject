#include "ParallelServer.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <thread>
#include <string>

namespace server_side{

    void ParallelServer::clientHandle(const client_handler::ClientHandler& ch){
        while(stop()){   
            if(waitingClients.size() > 0){
                mutexLock.lock();
                uint32_t currentClient = waitingClients.front();
                waitingClients.pop();
                ch.handleClient(currentClient);
                mutexLock.unlock();
            }
        }
    }

    void ParallelServer::open(uint32_t serverPort, const client_handler::ClientHandler& clientHandler) const {
      
       struct sockaddr_in clientAddress;
       struct sockaddr_in serverAddress;

       for(int i = 0; i < m_threadPoolSize ; ++i){
           threadPool.push_back(std::thread([this, &clientHandler]{
               ParallelServer::clientHandle(std::ref(clientHandler));
               }));
       }
        for(int i = 0; i < m_threadPoolSize ; ++i){
           threadPool.at(i).join();
       }

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

        //

        while(!stop()){
            //waiting for connections

            uint32_t addrSize = sizeof(clientAddress);

            auto clientSocket = accept(serverSocket, reinterpret_cast<sockaddr *>(&clientAddress)
            , reinterpret_cast<socklen_t*>(&addrSize));

            if(clientSocket < 0){
                //error
            }

            waitingClients.push(clientSocket);

        }
  
    }

    bool ParallelServer::stop() const{
        return false;
    }

}