//
// Created by YuHuanTin on 2023/11/19.
//

#ifndef BILIBILILIVEPROTOCOL_INTERFACE_H
#define BILIBILILIVEPROTOCOL_INTERFACE_H

#include <cstdint>
#include <memory>


#include "../Network/WS/WSSClient.h"
#include "../Network/Protocol/Protocol.h"
#include "../Network/Protocol/CommandParser.h"

namespace Interface {

    /**
     * start a websocket client and return if success, then recv the message and call the callback
     * return nullptr if fail
     * 
     * @param RoomID 
     * @param Callback 
     * @return 
     */
    std::unique_ptr<WSSClient> start(uint64_t RoomID, std::function<void(const ix::WebSocketMessagePtr &)> Callback);

    /**
     * parse command from server and return the message
     * return std::string("") if fail
     * 
     * @return 
     */
    std::string parseCommandData(const std::string &DataToParse);
    

} // Interface

#endif //BILIBILILIVEPROTOCOL_INTERFACE_H
