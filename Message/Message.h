//
// Created by Utente on 09/11/2026.
//

#ifndef CLIENT_MESSAGE_H
#define CLIENT_MESSAGE_H

int stringLenght(const char* stringa);
class Message {
    char* message;
    unsigned int lenght;

    void encripting(char*,const char KEY);
    void decripting(char*,const char KEY);
public:
    Message(const char* message);
    Message(const Message& message);
    ~Message();
    void decription(const char KEY);
    void encription(const char KEY);
    const char* print() const;
    unsigned int getLenght() const {return lenght;}
};


#endif //CLIENT_MESSAGE_H