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
    std::cout << "choose sink --\n 1 - wav \n 2 - WebSocket -\n 3 - wav and WebSocket\n";
    std::string chosen;
    getline(std::cin, chosen);
    int chooseNum = std::stoi(chosen);
    std::cout << "choose bit rate\n 1 - 16bit \n 2 - 24bit \n";
    std::string br;
    getline(std::cin, br);
    int ibr = std::stoi(br);

    switch (chooseNum)
    {
    case 1:
    {
        std::cout << "How many iterations?\n";
        std::string hm;
        getline(std::cin, hm);
        int ihm = std::stoi(hm);
        IComposer *co = nullptr;
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
        co->SetStream();
        co->StartFor(ihm);
        co->Close();
        break;
    }

    case 2:
    {
        if (ibr == 1)
        {

            std::cout << "chosen bit rate 16bit\n";
            WebSocketServer<int16_t, 88200> wss;
            wss.StartServer(9002);
        }
        else if (ibr == 2)
        {
            std::cout << "chosen bit rate 24bit\n";
            WebSocketServer<s24bit, 88200> wss;
            wss.StartServer(9002);
        }
    }

    case 3:
    {
        if (ibr == 1)
        {

            std::cout << "chosen bit rate 16bit\n";
            auto co = new Composer<int16_t, 96000>();
            co->ComposeStereoToWav();
            WebSocketServer<int16_t, 88200> wss;
            wss.StartServer(9002);
        }
        else if (ibr == 2)
        {
            std::cout << "chosen bit rate 24bit\n";
            auto co = new Composer<s24bit, 96000>();
            co->ComposeStereoToWav();
            WebSocketServer<s24bit, 88200> wss;
            wss.StartServer(9002);
        }
    }

    default:
        break;
    }

    return 0;
}