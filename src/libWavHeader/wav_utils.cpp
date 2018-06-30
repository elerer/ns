#include <WavHeader.h>
#include <iostream>
#include <string>
#include<fstream>

int main()
{
    std::cout << "enter wav file to examine?\n";
    std::string hm;
    getline(std::cin, hm);
    Wav_header wh;
    char buffer[1000];
    std::ifstream is(hm.c_str(), std::ifstream::binary);
    is.read(buffer, 1000);
    is.close();
    wh.FillHeader(buffer);
    wh.printHeader();

    return 0;
}