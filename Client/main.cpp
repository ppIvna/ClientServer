#include <iostream>
#include <string>
#include "Sender.h"
int main(){
    Sender channel("192.168.178.69", 0x67);
    if (!channel.connect()) {
        std::cerr << "Connection failed" << std::endl;
    }
    std::string input;
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