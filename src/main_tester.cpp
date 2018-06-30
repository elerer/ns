#include <iostream>
#include <AudioInterfaceManager.h>
#include <string>
#include <aimDefines.h>
#include <StreamCallbacks.h>
#include <thread>
#include <chrono>
#include <SimpleBufferedProxy.h>
#include <Composer.h>
#include <WebSocketServer.h>

int main()
{

    using namespace std::chrono_literals;
    std::cout << "hi\n";
    std::cout << "choose sink --\n 1 - wav \n 2 - WebSocket -\n";
    std::string chosen;
    getline(std::cin, chosen);
    int chooseNum = std::stoi(chosen);

    switch (chooseNum)
    {
    case 1:
    {
        std::cout << "How many iterations?\n";
        std::string hm;
        getline(std::cin, hm);
        int ihm = std::stoi(hm);
        IComposer *co = nullptr;
        std::cout << "choose bit rate\n 1 - 16bit \n 2 - 24bit \n";
        std::string br;
        getline(std::cin, br);
        int ibr = std::stoi(br);
        switch (ibr)
        {
        case 1:
            std::cout << "chosen bit rate 16bit\n";
            co = new Composer<int16_t, 96000>();
            break;
        case 2:
            std::cout << "chosen bit rate 24bit\n";
            co = new Composer<s24bit, 96000>();
            break;
        }

        co->ComposeStereoToWav();
        co->StartFor(ihm);
        co->Close();
        break;
    }

    case 2:
    {
        WebSocketServer<88200> wss;
        wss.StartServer(9002);
        break;
    }

    default:
        break;
    }

    return 0;
}