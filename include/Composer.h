#ifndef __COMPOSER__
#define __COMPOSER__
#include <AudioInterfaceManager.h>
#include <Composer.h>
#include <iostream>
#include <string>
#include <type_traits>
#include<StreamWriter.h>
#include<IStreamSink.h>
#include<WavFileSink.h>

template <typename T, int N>
class Composer
{
  public:
    Composer();
    void ComposeStereo();
    void Start();

  private: /*methods*/
    void letUserSelectDevice();
    void setSampleFormat();

  private:
    AudioInterfaceManager _aif;
    AudioInterfaceManager::StreamConfData _scd;
    std::unique_ptr<StreamWriter<T, N>> _streamWriter;
    size_t _deviceNum = 0;
    AudioInterfaceManager::SampleFormat _sf = AudioInterfaceManager::eInt16;
};

template <typename T, int N>
Composer<T, N>::Composer()
{
    setSampleFormat();
    _aif.InitInterface();
}

template <typename T, int N>
void Composer<T, N>::ComposeStereo()
{
    letUserSelectDevice();
    _aif.ListDeviceInformation(_deviceNum);
    IBufferedProxyProcessor<T> *rb = new SimpleBufferedProxy<T, N>();
    IStreamSink *ss = new WavFileSink();
    _streamWriter.reset(new StreamWriter<T, N>(rb, ss));
    
    _aif.SetStreamConfiguration(_deviceNum, 2, _sf, DEFAULT_SAMPLE_RATE, Int16ProxyInputSource, 1024, _scd, rb);
    _aif.SetStreamFromDevice(_scd);
}

template <typename T, int N>
void Composer<T, N>::setSampleFormat()
{
    if (std::is_floating_point<T>::value)
    {
        _sf = AudioInterfaceManager::eFloat;
    }
    if (std::is_integral<T>::value)
    {
        auto s = sizeof(T);
        switch (s)
        {
        case 8:
            _sf = AudioInterfaceManager::eInt8;
            break;
        case 16:
            _sf = AudioInterfaceManager::eInt16;
            break;
        case 24:
            _sf = AudioInterfaceManager::eInt24;
            break;
        case 32:
            _sf = AudioInterfaceManager::eInt32;
            break;
        default:
            break;
        }
    }
}

template <typename T, int N>
void Composer<T, N>::letUserSelectDevice()
{
    _aif.ListDevices();
    std::cout << "Which device do you want to query [index num] -\n";
    std::string devStrNum;
    getline(std::cin, devStrNum);
    _deviceNum = std::stoi(devStrNum);
}

template <typename T, int N>
void Composer<T, N>::Start()
{
    
    _aif.StartStream(_scd);
    _streamWriter->RunFor(20);
}

#endif