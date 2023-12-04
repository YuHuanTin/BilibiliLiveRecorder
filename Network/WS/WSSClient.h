//
// Created by YuHuanTin on 2023/12/4.
//

#ifndef BILIBILILIVEPROTOCOL_WSSCLIENT_H
#define BILIBILILIVEPROTOCOL_WSSCLIENT_H


#include "Client/WebSocketCore.h"

class WSSClient : public WebSocketCore {
private:
    uint64_t m_uid;
    uint64_t m_roomId;
    std::string m_token;
    std::string m_userCookie;
public:
    WSSClient(uint64_t mUid, uint64_t mRoomId, const std::string &mToken, const std::string &mUserCookie);

    WSSClient &sendAuthentication();

};


#endif //BILIBILILIVEPROTOCOL_WSSCLIENT_H
