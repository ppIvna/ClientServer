//
// Created by Utente on 09/11/2026.
//

#ifndef SERVER_RECEIVER_H
#define SERVER_RECEIVER_H
#include "../Message/Message.h"
#include <winsock2.h>
#include <ws2tcpip.h>
class Receiver {
    const char KEY;
    char** message;
    unsigned int counter;
    void AddMessage(const char*, unsigned int);
    char buffer[1024];
    SOCKET socketPath=INVALID_SOCKET;
    SOCKET clientSocket=INVALID_SOCKET;
    public:
    bool  startAndAccept(int port);
    Receiver(char KEY);
    const char *receiveMessage();
    ~Receiver();
};


#endif //SERVER_RECEIVER_H