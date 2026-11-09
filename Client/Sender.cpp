//
// Created by Utente on 06/11/2026.
//

#include "Sender.h"

Sender::Sender(const char* IP,const char KEY):KEY(KEY) {
    WSADATA wsaData;
    const unsigned int IPLenght=stringLenght(IP)+1;
    IPreceiver=new char[IPLenght];
    for (int i=0; i<IPLenght; i++) {
        IPreceiver[i]=IP[i];
    }
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Errore inizializzazione Winsock";
    }

    socketPath = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (socketPath==INVALID_SOCKET) {
        std::cerr << "Errore creazione socket";
    }
}

bool Sender::connect() const {

    sockaddr_in receiver{};

    receiver.sin_family = AF_INET;
    receiver.sin_port = htons(5000);

    if (inet_pton(AF_INET, IPreceiver,&receiver.sin_addr) != 1) {return false;}

    int result = ::connect(socketPath,reinterpret_cast<sockaddr*>(&receiver),sizeof(receiver));
    if (result == SOCKET_ERROR) {
        // AGGIUNGI QUESTA RIGA PER VEDERE IL CODICE DI ERRORE:
        std::cerr << "Errore connect(). Codice Winsock: " << WSAGetLastError() << std::endl;
        return false;
    }

    return result != SOCKET_ERROR;
}

Sender::~Sender() {
    delete[] IPreceiver;
    if (socketPath != INVALID_SOCKET) {
        closesocket(socketPath);
    }
    WSACleanup();
}

bool Sender::send(Message message) {
    if (socketPath == INVALID_SOCKET) {
        std::cerr << "Errore Socket non valido\n";
        return false;
    }
    message.encription(KEY);
    int bytesSent = ::send(socketPath, message.print(), message.getLenght(), 0);
    if (bytesSent == SOCKET_ERROR) {
        std::cerr << "Errore durante l'invio dei dati. Codice: " << WSAGetLastError() << std::endl;
        return false;
    }
    return true;
}
