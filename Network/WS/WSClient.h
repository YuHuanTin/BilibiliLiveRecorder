//
// Created by YuHuanTin on 2023/11/19.
//

#ifndef BILIBILILIVEPROTOCOL_WSCLIENT_H
#define BILIBILILIVEPROTOCOL_WSCLIENT_H


#include <string>

class WSClient {

public:
    std::string m_host;
    uint32_t m_port;
    std::string m_token;

    WSClient(std::string Host, uint32_t Port, std::string Token);

    void start();

    void stop();

};


#endif //BILIBILILIVEPROTOCOL_WSCLIENT_H
