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
template <typename T, int N>
class WebSocketServer
{
public:
  typedef std::pair<std::unique_ptr<Composer<T, N>>, WebSocketSink<N> *> compNsink;
  typedef websocketpp::server<websocketpp::config::asio>::message_ptr message_ptr;


  void on_open(websocketpp::server<websocketpp::config::asio> *s, websocketpp::connection_hdl hdl);
  void on_message(websocketpp::server<websocketpp::config::asio> *s, websocketpp::connection_hdl hdl,message_ptr msg);
  //TODO on_close - stop and delete the composer

  void StartServer(const int &port);

private: /*members*/
  std::mutex _mapMutex;
  websocketpp::server<websocketpp::config::asio> _server;
  std::map<websocketpp::connection_hdl, compNsink, std::owner_less<websocketpp::connection_hdl>> _conToSinkMap;
};

template <typename T, int N>
void WebSocketServer<T, N>::on_open(websocketpp::server<websocketpp::config::asio> *s, websocketpp::connection_hdl hdl)
{

  auto ws = new WebSocketSink<N>(&_server, hdl);

  auto co = new Composer<T, N>();
  co->ComposeStereoToWebSocket(ws);
  co->SetStream();
  std::cout << "Starting to stream\n";
  co->StartStreamToSinks();

  {
    std::unique_lock<std::mutex> lock1(_mapMutex);

    if (_conToSinkMap.find(hdl) != _conToSinkMap.end())
    {
      //LOg error
      return;
    }
    _conToSinkMap.insert(std::make_pair(hdl, std::make_pair(std::unique_ptr<Composer<T, N>>(co), ws)));
  }
}

// Define a callback to handle incoming messages
template <typename T, int N>

void WebSocketServer<T, N>::on_message(websocketpp::server<websocketpp::config::asio> *s, websocketpp::connection_hdl hdl, message_ptr msg)
{

  std::cout << "on_message called with hdl: " << hdl.lock().get()
            << " and message: " << msg->get_payload()
            << std::endl;

  if (msg->get_payload() == "start")
  {
    WebSocketSink<N> *ws = nullptr;
    {
      std::unique_lock<std::mutex> lock1(_mapMutex);
      auto it = _conToSinkMap.find(hdl);
      if (it == _conToSinkMap.end())
      {
        //didnt find LOg error
        return;
      }
      ws = it->second.second;
    }
    std::cout << "Cancelling zeros\n";
    ws->_streamZeros = false;
    return;
  }
}

template <typename T, int N>
void WebSocketServer<T, N>::StartServer(const int &port)
{
  std::cout << "starting WebSocket server on port " << port << "\n";
  // Set logging settings
  //_server.set_access_channels(websocketpp::log::alevel::all);
  //_server.clear_access_channels(websocketpp::log::alevel::frame_payload);

  // Initialize ASIO
  _server.init_asio();

  _server.set_open_handler(bind(&WebSocketServer<T, N>::on_open, this, &_server, ::_1));

  // Register our message handler
  _server.set_message_handler(bind(&WebSocketServer<T, N>::on_message, this, &_server, ::_1, ::_2));

  // Listen on port 9002
  _server.listen(port);

  // Start the server accept loop
  _server.start_accept();

  // Start the ASIO io_service run loop
  _server.run();
}
#endif
