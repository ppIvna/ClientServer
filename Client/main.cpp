#include <iostream>
#include <string>
#include "Sender.h"
bool ValidIP(std::string ip) {
    std::string subStr;
    int j=0;
    for (int i=0; i<4; i++) {
        subStr="";
        while (ip.size()>j&&(ip[j]!='.'||i==3)) {
            subStr += ip[j];
            j++;
        }
        try {
            int value = std::stoi(subStr);
        }
        catch (const std::invalid_argument& e) {
            return false;
        }
        catch (const std::out_of_range& e) {
            return false;
        }
        if (std::stoi(subStr)>255||std::stoi(subStr)<0) {
            return false;
        }
        if (i==3&&(std::stoi(subStr)==255||std::stoi(subStr)==0)) {
            return false;
        }
        j++;
    }
    return true;
}
int main(){
    std::string input;
    bool validIP;
    do {
        std::cout << "Inserisci l'indirizzo IPv4 locale del server(assicurati di aver attivato la porta 5000): " << std::endl;
        std::getline(std::cin, input);
        validIP=ValidIP(input);
        if (!validIP) {
            std::cout<<"Indirizzo IP non valido, prova con un altro"<<std::endl;
        }
        else {
            std::cout<<"IP valido provo la connessione al dispositivo: "<<input<<std::endl;
        }
    }while (!validIP);
    Sender channel(input.c_str(), 0x67);
    if (!channel.connect()) {
        std::cerr << "Connection failed" << std::endl;
    }
    while (true) {
        std::cout << "Inserisci il comando da inviare al server: " << std::endl;
        std::getline(std::cin, input);
        if (input == "exit") {
            break;
        }
        Message packet(input.c_str());
        channel.send(packet);
    }
}