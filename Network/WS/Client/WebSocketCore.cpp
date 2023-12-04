//
// Created by YuHuanTin on 2023/11/19.
//

#include "WebSocketCore.h"

#include "ixwebsocket/IXNetSystem.h"
#include "../../../Utils/ExpectionHelper/ExpectionHelper.h"
#include "../Type/ExceptionType.h"

WebSocketCore::WebSocketCore() {
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

WebSocketCore &WebSocketCore::start() {
    m_ptr_websocket->start();
    return *this;
}

WebSocketCore &WebSocketCore::send(const std::vector<uint8_t> &DataToSend) {
    m_ptr_websocket->sendBinary(DataToSend);
    return *this;
}

WebSocketCore &WebSocketCore::stop() {
    m_ptr_websocket->close();
    return *this;
}

WebSocketCore &WebSocketCore::setUrl(const std::string &Url) {
    m_ptr_websocket->setUrl(Url);
    return *this;
}

WebSocketCore &WebSocketCore::setPingInterval(int PingInterval) {
    m_ptr_websocket->setPingInterval(PingInterval);
    return *this;
}

WebSocketCore &WebSocketCore::setPingMessage(const std::vector<uint8_t> &PingMessage) {
    std::string str(PingMessage.begin(), PingMessage.end());
    m_ptr_websocket->setPingMessage(str, ix::SendMessageKind::Binary);
    return *this;
}

WebSocketCore &
WebSocketCore::setMessageCallback(const std::function<void(const ix::WebSocketMessagePtr &)> &MessageCallback) {
    m_ptr_websocket->setOnMessageCallback(MessageCallback);
    return *this;
}

WebSocketCore::~WebSocketCore() {
    try {
        if (!ix::uninitNetSystem()) {
            throw ExpectionType::Net_Uninit_Failed{};
        }
    } catch (std::exception &Exception) {
        ExpectionHelper::dumpExpection("wss client destroy failed", Exception);
    }
}


