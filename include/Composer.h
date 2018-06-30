#ifndef __COMPOSER__
#define __COMPOSER__
#include <AudioInterfaceManager.h>
#include <Composer.h>
#include <iostream>
#include <string>
#include <type_traits>
#include <StreamWriter.h>
#include <IStreamSink.h>
#include <WavFileSink.h>
#include <atomic>
#include <thread>
#include <ctime>
#include <sstream>

class IComposer
{
  public:
    virtual ~IComposer() {}
    virtual void ComposeStereoToWav() = 0;
    virtual void StartStreamToSinks() = 0;
    virtual void StartFor(const size_t &f) = 0; 
    virtual void Close() = 0;
};

template <typename T, int N>
class Composer : public IComposer
{
  public:
    Composer();
    void ComposeStereoToWav() override;
    void ComposeStereoToWebSocket(IStreamSink *ws);
    //TODO composition of multiple sinks
    void StartFor(const size_t &f) override;
    void StartStreamToSinks();
    void Close() override;
    std::atomic_bool _continue;

  private: /*methods*/
    void letUserSelectDevice();
    void setSampleFormat();
    void setCallBack();

  private:
    AudioInterfaceManager _aif;
    AudioInterfaceManager::StreamConfData _scd;
    std::unique_ptr<StreamWriter<T, N>> _streamWriter; //owner simple buffer
    std::unique_ptr<IStreamSink> _sink;
    size_t _deviceNum = 0;
    AudioInterfaceManager::SampleFormat _sf = AudioInterfaceManager::eInt16;
    std::string _wavFileName = "date_";
    PaStreamCallback* _cb;
};

template <typename T, int N>
Composer<T, N>::Composer()
{
    _continue = true;
    setSampleFormat();
    setCallBack();
    _aif.InitInterface();
}

template <typename T, int N>
void Composer<T, N>::ComposeStereoToWav()
{
    std::time_t result = std::time(nullptr);
    std::stringstream s;
    s << result;
    std::string ts = s.str();
    std::string wfn = _wavFileName + ts + ".wav";
    letUserSelectDevice();
    _aif.ListDeviceInformation(_deviceNum);
    IBufferedProxyProcessor<T> *rb = new SimpleBufferedProxy<T, N>();
    IStreamSink *ss = new WavFileSink(2, DEFAULT_SAMPLE_RATE, sizeof(T) * 8, wfn, "/var/tmp/", "/home/eranl/WAV_FILES/");
    _streamWriter.reset(new StreamWriter<T, N>(rb, ss));
    _sink.reset(ss);

    _aif.SetStreamConfiguration(_deviceNum, 2, _sf, DEFAULT_SAMPLE_RATE, _cb, 1024, _scd, rb);
    _aif.SetStreamFromDevice(_scd);
}

template <typename T, int N>
void Composer<T, N>::ComposeStereoToWebSocket(IStreamSink *ws)
{
    _sink.reset(ws);
    letUserSelectDevice();
    _aif.ListDeviceInformation(_deviceNum);
    IBufferedProxyProcessor<T> *rb = new SimpleBufferedProxy<T, N>();
    _streamWriter.reset(new StreamWriter<T, N>(rb, ws));

    _aif.SetStreamConfiguration(_deviceNum, 2, _sf, DEFAULT_SAMPLE_RATE, _cb, 1024, _scd, rb);
    _aif.SetStreamFromDevice(_scd);
}

template <typename T, int N>
void Composer<T, N>::setCallBack()
{
    switch (_sf)
    {
    case AudioInterfaceManager::eInt16:
        std::cout << "setting callback of 16bit\n";
        _cb = Int16ProxyInputSource;
        break;
    case AudioInterfaceManager::eInt24:
        std::cout << "setting callback of 24bit\n";
        _cb = Int24ProxyInputSource;
        break;
    default:
        break;
    }
}

template <typename T, int N>
void Composer<T, N>::setSampleFormat()
{
    std::cout << "Set sample Format - size of T " << sizeof(T) << "\n";
    if (std::is_floating_point<T>::value)
    {
        std::cout << "T is float";
        _sf = AudioInterfaceManager::eFloat;
    }
    else
    {
        auto s = sizeof(T);
        switch (s)
        {
        case 1:
            _sf = AudioInterfaceManager::eInt8;
            std::cout << "setting AudioInterfaceManager::eInt8 \n";
            break;
        case 2:
            _sf = AudioInterfaceManager::eInt16;
            std::cout << "setting AudioInterfaceManager::eInt16 \n";
            break;
        case 3:
            _sf = AudioInterfaceManager::eInt24;
            std::cout << "setting AudioInterfaceManager::eInt24 \n";
            break;
        case 4:
            _sf = AudioInterfaceManager::eInt32;
            std::cout << "setting AudioInterfaceManager::eInt32 \n";
            break;
        default:
            std::cout << "DEFAULT \n";
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
void Composer<T, N>::StartFor(const size_t &f)
{
    _aif.StartStream(_scd);
    _streamWriter->RunFor(f); //TODO for now runfor instead of run
}

template <typename T, int N>
void Composer<T, N>::StartStreamToSinks()
{
    _aif.StartStream(_scd);
    std::thread tsw(&StreamWriter<T, N>::Run, _streamWriter.get());
    std::thread tsink(&IStreamSink::Run, _sink.get());

    tsw.detach();
    tsink.detach();
}

template <typename T, int N>
void Composer<T, N>::Close()
{
    _continue = false;
    _aif.CloseStream(_scd);
    // _streamWriter->Close();
    _sink->Close();
    //TODO what else we need to clean ? portaudio ? callback ?
}

#endif