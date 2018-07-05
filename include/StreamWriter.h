#ifndef __STREAMWRITER__
#define __STREAMWRITER__
#include <IBufferedProxyProcessor.h>
#include <IStreamSink.h>
#include <memory>
#include <atomic>
#include <vector>
//Glue between the ring buffer and stream sink
template <typename T, size_t N>
class StreamWriter
{
  public:
    StreamWriter(IBufferedProxyProcessor<T> *rb);
    void StreamBytes(const size_t &num);
    size_t ConsumeAndWrite();
    //Run this class as thread
    void Run();
    void RunFor(size_t i);
    void AddSink(IStreamSink *s);

    std::atomic<bool> _continue;

  private:
    //shared with callback
    std::unique_ptr<IBufferedProxyProcessor<T>> _ringBuffer;

    std::vector<IStreamSink*> _sinks;
    std::unique_ptr<char[]> _bytes;
    //manged by the unique_ptr
    char *_pBytes;

    size_t _elemSize = 0;
    size_t _numelems = 0;
};

template <typename T, size_t N>
StreamWriter<T, N>::StreamWriter(IBufferedProxyProcessor<T> *rb) : _continue(true)
{
    _elemSize = sizeof(T);
    _numelems = N;
    _ringBuffer.reset(rb);
    _pBytes = new char[_elemSize * _numelems];
    _bytes.reset(_pBytes);
}

template <typename T, size_t N>
void StreamWriter<T, N>::StreamBytes(const size_t &num)
{
    for (auto sink : _sinks)
    {
        sink->StreamBytes(_pBytes, num);
    }
}

template <typename T, size_t N>
void StreamWriter<T, N>::Run()
{
    while (_continue)
    {
        ConsumeAndWrite();
    }
}

template <typename T, size_t N>
void StreamWriter<T, N>::RunFor(size_t i)
{
    while (i > 0)
    {
        if (ConsumeAndWrite() > 0)
            i--;
    }
}

template <typename T, size_t N>
size_t StreamWriter<T, N>::ConsumeAndWrite()
{
    size_t numread = 0;
    numread = _ringBuffer->Pop((T *)_pBytes, _numelems);
    if (numread > 0)
        StreamBytes(numread * sizeof(T));
    return numread;
}

template <typename T, size_t N>
void StreamWriter<T, N>::AddSink(IStreamSink *s)
{
    _sinks.push_back(s);
}
#endif