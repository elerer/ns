#include <iostream>
#include <AudioInterfaceManager.h>
#include <string>
#include <aimDefines.h>
#include <StreamCallbacks.h>
#include <thread>
#include <chrono>
#include <SimpleBufferedProxy.h>
#include<Composer.h>
#include<WebSocketServer.h>


int main()
{
    /*
    using namespace std::chrono_literals;
    std::cout << "hi\n";
    Composer<int16_t,88200> co;
    co.ComposeStereo();
    co.Start();
    */
    WebSocketServer<88200> wss;
    wss.StartServer(9002);

    return 0;
}