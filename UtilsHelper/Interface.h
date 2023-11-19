//
// Created by YuHuanTin on 2023/11/19.
//

#ifndef BILIBILILIVEPROTOCOL_INTERFACE_H
#define BILIBILILIVEPROTOCOL_INTERFACE_H

#include <cstdint>
#include <memory>


#include "../Network/WS/WSClient.h"

namespace Interface {

    std::unique_ptr<WSClient> start(uint64_t RoomID);


} // Interface

#endif //BILIBILILIVEPROTOCOL_INTERFACE_H
