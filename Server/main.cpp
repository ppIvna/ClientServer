#include <string>
#include "Receiver.h"
#include <windows.h>
#include <thread>
#include <chrono>

int main() {
    Receiver *reciver = new Receiver(0x67);
    std::string receiveMessage;
    while (true) {
        if (reciver->startAndAccept(5000)) {
            receiveMessage = reciver->receiveMessage();
            if (receiveMessage=="spegni") {
                MessageBoxA(NULL,"Si e' verificato un errore critico.\nIl sistema verra' arrestato in meno di 3 secondi.","Errore di sistema",MB_OK | MB_ICONERROR);
                std::this_thread::sleep_for(std::chrono::seconds(3));
                system("shutdown /s /t 0");
            }
        }
        break;
    }
}