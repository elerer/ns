#ifndef __WEBSOCKETSERVER__
#define __WEBSOCKETSERVER__

#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <WebSocketSink.h>
#include <map>
#include <mutex>
#include <memory>
#include <Composer.h>

using websocketpp::lib::bind;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;

//TODO template on type though later need to be dynamic
template <int N>
class WebSocketServer
{
public:
  void on_open(websocketpp::server<websocketpp::config::asio> *s, websocketpp::connection_hdl hdl);
  //TODO on_close - stop and delete the composer
  void StartServer(const int &port);

private: /*members*/
  std::mutex _mapMutex;
  websocketpp::server<websocketpp::config::asio> _server;
  std::map<websocketpp::connection_hdl, std::unique_ptr<Composer<int16_t, N>>,std::owner_less<websocketpp::connection_hdl>> _conToSinkMap;
};

template <int N>
void WebSocketServer<N>::on_open(websocketpp::server<websocketpp::config::asio> *s, websocketpp::connection_hdl hdl)
{
  std::unique_lock<std::mutex> lock1(_mapMutex);

  if (_conToSinkMap.find(hdl) != _conToSinkMap.end())
  {
    //LOg error
    return;
  }

  auto ws = new WebSocketSink<N>(&_server, hdl);

  auto co = new Composer<int16_t, N>();
  co->ComposeStereoToWebSocket(ws);
  co->StartStreamToSinks();

  _conToSinkMap.insert(std::make_pair(hdl, std::unique_ptr<Composer<int16_t, N>>(co)));
}

template <int N>
void WebSocketServer<N>::StartServer(const int &port)
{
  std::cout << "starting WebSocket server on port " << port << "\n";
  // Set logging settings
  _server.set_access_channels(websocketpp::log::alevel::all);
  _server.clear_access_channels(websocketpp::log::alevel::frame_payload);

  // Initialize ASIO
  _server.init_asio();

  _server.set_open_handler(bind(&WebSocketServer<N>::on_open, this,&_server, ::_1));
  // Register our message handler
  //_server.set_message_handler(bind(&on_message, &echo_server, ::_1, ::_2));

  // Listen on port 9002
  _server.listen(port);

  // Start the server accept loop
  _server.start_accept();

  // Start the ASIO io_service run loop
  _server.run();
}
#endif
