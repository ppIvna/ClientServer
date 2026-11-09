//
// Created by Utente on 09/11/2026.
//

#include "Message.h"

int stringLenght(const char* stringa) {
    int length=0;
    while (stringa[length]!='\0') {
        length++;
    }
    return length;
}
Message::Message(const char *message){
    lenght=stringLenght(message)+1;
    this->message=new char[lenght];
    for (int i=0;message[i]!='\0';i++) {
        this->message[i]=message[i];
    }
    this->message[lenght-1]='\0';
}

void Message::encripting(char* string, const char KEY) {
    if (*(string+1)=='\0') {
        *string+=*message&0x0F;
        return;
    }
    *string+=*(string+1)&0x0F;
    *string^=KEY;
    encripting(string+1, KEY);
}

void Message::decripting(char* string, const char KEY) {//***TEMPORENEA*** tenerla per spostarla nel server
    if (*(string+1)=='\0') {
        *string-=*message&0x0F;
        return;
    }
    decripting(string+1,KEY);
    *string^=KEY;
    *string-=*(string+1)&0x0F;
}

void Message::decription(const char KEY) {
    this->decripting(message, KEY);

}

void Message::encription(const char KEY) {
    this->encripting(message, KEY);
}

const char* Message::print() const {
    return message;
}

Message::Message(const Message &message) {
    lenght=message.getLenght();
    this->message=new char[lenght];
    const char* tempArray=message.print();
    for (int i=0;i<lenght;i++) {
        this->message[i]=tempArray[i];
    }
}

Message::~Message() {
    delete[] message;
}
