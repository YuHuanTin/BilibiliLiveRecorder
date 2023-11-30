//
// Created by YuHuanTin on 2023/11/19.
//

#ifndef BILIBILILIVEPROTOCOL_INTERFACE_H
#define BILIBILILIVEPROTOCOL_INTERFACE_H

#include <cstdint>
#include <memory>


#include "../Network/WS/Client/WSClient.h"
#include "../Network/Protocol/Protocol.h"

namespace Interface {
    struct StartResult {
        std::unique_ptr<WSClient> Websocket;
        uint64_t RoomID;
        std::string Token;
    };

    StartResult start(uint64_t RoomID);


} // Interface

#endif //BILIBILILIVEPROTOCOL_INTERFACE_H
