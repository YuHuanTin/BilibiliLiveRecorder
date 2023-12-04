//
// Created by YuHuanTin on 2023/11/19.
//

#ifndef BILIBILILIVEPROTOCOL_WEBSOCKETCORE_H
#define BILIBILILIVEPROTOCOL_WEBSOCKETCORE_H


#include <string>
#include <functional>
#include <ixwebsocket/IXWebSocket.h>


class WebSocketCore {
private:
    std::unique_ptr<ix::WebSocket> m_ptr_websocket;

public:
    WebSocketCore();

    WebSocketCore &start();

    WebSocketCore &send(const std::vector<uint8_t> &DataToSend);

    WebSocketCore &stop();

    WebSocketCore &setUrl(const std::string &Url);

    WebSocketCore &setPingInterval(int PingInterval);

    WebSocketCore &setPingMessage(const std::vector<uint8_t> &PingMessage);

    WebSocketCore &setMessageCallback(const std::function<void(const ix::WebSocketMessagePtr &)> &MessageCallback);

    ~WebSocketCore();
};


#endif //BILIBILILIVEPROTOCOL_WEBSOCKETCORE_H
