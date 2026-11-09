

#ifndef DROPPER_SENDER_H
#define DROPPER_SENDER_H
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include "../Message/Message.h"


class Sender {
    const char KEY;
    char* IPreceiver;
    SOCKET socketPath=INVALID_SOCKET;
public:
    Sender(const char* IP, char KEY);
    ~Sender();
    bool connect() const;
    bool send(Message message);
};


#endif //DROPPER_SENDER_H