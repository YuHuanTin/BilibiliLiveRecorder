//
// Created by YuHuanTin on 2023/11/19.
//

#include "WSClient.h"

#include <utility>
#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXNetSystem.h>

#include "../../UtilsHelper/ExpectionHelper/ExpectionHelper.h"

WSClient::WSClient(std::string Host, uint32_t Port, std::string Token)
        : m_host(std::move(Host)), m_port(Port), m_token(std::move(Token)) {}

void WSClient::start() {
    try {
        if (!ix::initNetSystem()) {
            throw std::runtime_error("ix::initNetSystem failed");
        }

        ix::WebSocket webSocket;
        webSocket.setUrl("wss://" + m_host + ":" + std::to_string(m_port));
        webSocket.setPingInterval(25);
        webSocket.setPingMessage(danmuProtocol.makePackage("[object Object]", WS_OP_HEARTBEAT),
                                 ix::SendMessageKind::Binary);

    } catch (std::exception &Exception) {
        ExpectionHelper::dumpExpection("ws·þÎñÆ÷Æô¶¯Ê§°Ü", Exception);
    }
}

void WSClient::stop() {
    try {
        // todo

        if (!ix::uninitNetSystem()) {
            throw std::runtime_error("ix::uninitNetSystem failed");
        }
    } catch (std::exception &Exception) {
        ExpectionHelper::dumpExpection("ws·þÎñÆ÷Í£Ö¹Ê§°Ü", Exception);
    }
}
