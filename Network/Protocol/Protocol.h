#ifndef BILIBILILIVEPROTOCOL_PROTOCOL_H
#define BILIBILILIVEPROTOCOL_PROTOCOL_H

#include "../../DataStruct/DataStruct.h"

class Protocol {
private:
    uint64_t uid = 0;
    uint64_t realRoomID = 0;
    std::string token;
public:
    Protocol(uint64_t Uid, uint64_t RealRoomID, std::string Token) : uid(Uid),
                                                                     realRoomID(RealRoomID),
                                                                     token(std::move(Token)) {}

    // ������
    std::vector<nlohmann::json> parsePackageToJson(const std::string &Buf);

    // ������
    std::string makePackage(const std::string &Buf, WSMsgTypeE WsMsg);

    // ������֤��
    std::string makeAuthenticationPackage();
};


#endif //BILIBILILIVEPROTOCOL_PROTOCOL_H
