#ifndef __WEBSOCKETSINK__
#define __WEBSOCKETSINK__
#include <IStreamSink.h>
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <SimpleBufferedProxy.h>
#include <atomic>

template <int N> //TODO maybe size should be dynamic ?
class WebSocketSink : public IStreamSink
{
public:
  WebSocketSink(websocketpp::server<websocketpp::config::asio> *server, websocketpp::connection_hdl hdl);
  void StreamBytes(char *src, const size_t &num) override;
  void Close() override;
  void Run();
  std::atomic_bool _continue;
  std::atomic_int _chunkSize;
  bool _streamZeros = true;

private: /*members*/
  websocketpp::server<websocketpp::config::asio> *_server;
  websocketpp::connection_hdl _hdl;
  SimpleBufferedProxy<char, N> _buffer;
  char _chunkBuffer[N];      //TODO decide value
  char _zeroBuffer[N] = {0}; //TODO decide value
};

template <int N>
WebSocketSink<N>::WebSocketSink(websocketpp::server<websocketpp::config::asio> *server, websocketpp::connection_hdl hdl) : _server(server),
                                                                                                                           _hdl(hdl)
{
  _chunkSize = 1024;
  _continue = true;
}

template <int N>
void WebSocketSink<N>::StreamBytes(char *src, const size_t &num)
{
  _buffer.Push(src, num);
}

template <int N>
void WebSocketSink<N>::Run()
{
  while (_continue)
  {
    if (!_server)
    {

      //TODO LOG - No server
      return;
    }
    if (_buffer.ReadAvailable() < _chunkSize)
    {
      continue; //TODO sleep?? maybe set to smaller value till buffer fills again to desired chunk
    }
    _buffer.Pop(_chunkBuffer, _chunkSize);
    _server->send(_hdl, _streamZeros ? _zeroBuffer :  _chunkBuffer, _chunkSize.load(), websocketpp::frame::opcode::binary);
  }
}

template <int N>
void WebSocketSink<N>::Close()
{
  _continue = false;
}

#endif