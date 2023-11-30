//
// Created by YuHuanTin on 2023/11/19.
//

#ifndef BILIBILILIVEPROTOCOL_WSCLIENT_H
#define BILIBILILIVEPROTOCOL_WSCLIENT_H


#include <string>
#include <functional>
#include <ixwebsocket/IXWebSocket.h>


class WSClient {
private:
    std::unique_ptr<ix::WebSocket> m_ptr_websocket;

public:
    WSClient();

    WSClient &start();

    WSClient &send(const std::vector<uint8_t> &DataToSend);

    WSClient &stop();

    WSClient &setUrl(const std::string &Url);

    WSClient &setPingInterval(int PingInterval);

    WSClient &setPingMessage(const std::vector<uint8_t> &PingMessage);

    WSClient &setMessageCallback(const std::function<void(const ix::WebSocketMessagePtr &)> &MessageCallback);

    ~WSClient();
};


#endif //BILIBILILIVEPROTOCOL_WSCLIENT_H
