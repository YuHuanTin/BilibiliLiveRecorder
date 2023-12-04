//
// Created by YuHuanTin on 2023/12/4.
//

#include "WSSClient.h"


#include "../Protocol/Protocol.h"

WSSClient::WSSClient(uint64_t mUid, uint64_t mRoomId, const std::string &mToken, const std::string &mUserCookie) : m_uid(
        mUid), m_roomId(mRoomId), m_token(mToken), m_userCookie(mUserCookie) {}

WSSClient &WSSClient::sendAuthentication() {
    this->send(Protocol::make_authentication_package(m_uid, m_roomId, m_token, m_userCookie));
    return *this;
}
