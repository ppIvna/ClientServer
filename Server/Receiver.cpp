//
// Created by Utente on 09/11/2026.
//

#include "Receiver.h"

Receiver::Receiver(const char KEY) : KEY(KEY) {
    WSADATA wsaData;
    counter=0;
    message = new char*[1];
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
    }

    socketPath = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}
const char* Receiver::receiveMessage() {
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    buffer[bytesReceived] = '\0';
    Message mes(buffer);
    mes.decription(KEY);
    AddMessage(mes.print(), bytesReceived+1);
    return mes.print();
}
void Receiver::AddMessage(const char* message,unsigned int lenght) {
    {//aumenta le dimensione dei message
        char** temp=new char*[counter];
        for (unsigned int i=0;i<counter;i++) {
            temp[i] = this -> message[i];
        }
        delete[] this->message;
        this->message = new char*[counter+1];
        for (unsigned int i=0;i<counter;i++) {
            this->message[i]=temp[i];
        }
        delete[] temp;
    }
    this->message[counter] = new char[lenght];
    for (unsigned int i=0;i<lenght;i++) {
        this->message[counter][i] = message[i];
    }
    counter++;
}
Receiver::~Receiver() {
    for (unsigned int i=0;i<counter;i++) {
        delete[] message[i];
    }
    if (socketPath != INVALID_SOCKET) {
        closesocket(socketPath);
    }
    if (clientSocket!= INVALID_SOCKET)
        closesocket(clientSocket);
    WSACleanup();
}
bool Receiver::startAndAccept(int port) {
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(socketPath, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        return false;
    }

    if (listen(socketPath, SOMAXCONN) == SOCKET_ERROR) {
        return false;
    }


    sockaddr_in clientAddr{};
    int clientLen = sizeof(clientAddr);

    // ACCETTIAMO il client e salviamo il socket dedicato alla comunicazione
    clientSocket = accept(socketPath, reinterpret_cast<sockaddr*>(&clientAddr), &clientLen);
    if (clientSocket == INVALID_SOCKET) {
        return false;
    }
    return true;
}
