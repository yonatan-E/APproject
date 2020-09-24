#include "ParallelServer.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <thread>
#include <string>

namespace server_side{

    static void clientHandle(std::mutex& mutexLock, std::queue<uint32_t>& waitingClients, const client_handler::ClientHandler& ch){
        while(true){   
            mutexLock.lock();
            uint32_t currentClient;
            if(waitingClients.size() > 0){
                std::cout << "in" << std::endl;
                std::cout << waitingClients.size() << std::endl;
                currentClient = waitingClients.front();
                waitingClients.pop();
                ch.handleClient(currentClient); 
            }
            mutexLock.unlock();
        }
    }

    void ParallelServer::open(uint32_t serverPort, const client_handler::ClientHandler& clientHandler) const {
       struct sockaddr_in clientAddress;
       struct sockaddr_in serverAddress;

       std::cout << "here 1" << std::endl;

       std::mutex m_mutexLock;

       for(int i = 0; i < m_threadPoolSize ; ++i){
           m_threadPool.push_back(std::thread(clientHandle, std::ref(m_mutexLock), std::ref(m_waitingClients), std::ref(clientHandler)));
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
        
        std::cout << "here 2" << std::endl;
        
        while(!stop()){
            //waiting for connections

            uint32_t addrSize = sizeof(clientAddress);

            auto clientSocket = accept(serverSocket, reinterpret_cast<sockaddr *>(&clientAddress)
            , reinterpret_cast<socklen_t*>(&addrSize));

            if(clientSocket < 0){
                //error
            }

            m_waitingClients.push(clientSocket);

        }
  
    }

    bool ParallelServer::stop() const{
        return false;
    }

}