#include "SerialServer.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>

namespace server{

     const uint32_t m_backlog = 20;

     void SerialServer::open(const uint32_t serverPort, const clientside::ClientHandler& clientHandler) const{
       
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


/**
        fd_set currentSockets, readySockets;
        FD_ZERO(&currentSockets);
        FD_SET(serverSocket, &currentSockets);

        while(!stop()){

            readySockets = currentSockets;

            struct timeval tv;
            tv.tv_sec = 5;
            tv.tv_usec = 0;

            if(select(FD_SETSIZE, &readySockets, nullptr, nullptr, nullptr) < 0){
                //error
            }

            uint32_t addrSize = sizeof(clientAddress);

            for(int i = 0 ; i < FD_SETSIZE ; ++i){
                if(FD_ISSET(i, &readySockets)){
                    if(i == serverSocket){
                        const uint32_t clientSocket = accept(serverSocket, reinterpret_cast<struct sockaddr *>(&clientAddress)
                        ,reinterpret_cast<socklen_t*>(&addrSize));
                         if(clientSocket < 0){
                             //error
                         }
                         FD_SET(clientSocket, &currentSockets);
                    }else{
                       clientHandler.handleClient(i);
                        FD_CLR(i, &currentSockets);
                    }
                }
            }

            //waiting for connections
  
        }
        **/


    }

    bool SerialServer::stop() const{
        return false;
    }

}