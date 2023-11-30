//
// Created by YuHuanTin on 2023/11/19.
//

#include "WSClient.h"

#include "ixwebsocket/IXNetSystem.h"
#include "../../../Utils/ExpectionHelper/ExpectionHelper.h"
#include "../Type/ExceptionType.h"

WSClient::WSClient() {
    try {
        /// init net system
        if (!ix::initNetSystem()) {
            throw ExpectionType::Net_Init_Failed{};
        }


        /// allocate websocket
        m_ptr_websocket = std::make_unique<ix::WebSocket>();
    } catch (std::exception &Exception) {
        ExpectionHelper::dumpExpection("wss client create failed", Exception);
    }
}

WSClient &WSClient::start() {
    m_ptr_websocket->start();
    return *this;
}

WSClient &WSClient::send(const std::vector<uint8_t> &DataToSend) {
    m_ptr_websocket->sendBinary(DataToSend);
    return *this;
}

WSClient &WSClient::stop() {
    m_ptr_websocket->close();
    return *this;
}

WSClient &WSClient::setUrl(const std::string &Url) {
    m_ptr_websocket->setUrl(Url);
    return *this;
}

WSClient &WSClient::setPingInterval(int PingInterval) {
    m_ptr_websocket->setPingInterval(PingInterval);
    return *this;
}

WSClient &WSClient::setPingMessage(const std::vector<uint8_t> &PingMessage) {
    std::string str(PingMessage.begin(), PingMessage.end());
    m_ptr_websocket->setPingMessage(str, ix::SendMessageKind::Binary);
    return *this;
}

WSClient &WSClient::setMessageCallback(const std::function<void(const ix::WebSocketMessagePtr &)> &MessageCallback) {
    m_ptr_websocket->setOnMessageCallback(MessageCallback);
    return *this;
}

WSClient::~WSClient() {
    try {
        if (!ix::uninitNetSystem()) {
            throw ExpectionType::Net_Uninit_Failed{};
        }
    } catch (std::exception &Exception) {
        ExpectionHelper::dumpExpection("wss client destroy failed", Exception);
    }
}


