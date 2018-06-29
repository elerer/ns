#include <WebSocketSink.h>

WebSocketSink::WebSocketSink(websocketpp::server<websocketpp::config::asio> *server,websocketpp::connection_hdl hdl)
_server(server),
_hdl(hdl)
{

}
void WebSocketSink::StreamBytes(char *src, const size_t &num)
{
    if (!server)
    {

        //LOG - No server
        return;
    }
    _server->send(_hdl, src, num, websocketpp::frame::opcode::binary);
}

void WebSocketSink::Close()
{
}