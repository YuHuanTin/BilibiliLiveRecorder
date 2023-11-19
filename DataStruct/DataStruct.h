#ifndef BILIBILILIVEPROTOCOL_DATASTRUCT_H
#define BILIBILILIVEPROTOCOL_DATASTRUCT_H

import <cstdint>;

enum WSMsgTypeE {
    WS_OP_HEARTBEAT = 2,
    WS_OP_HEARTBEAT_REPLY = 3,
    WS_OP_MESSAGE = 5,
    WS_OP_USER_AUTHENTICATION = 7,
    WS_OP_CONNECT_SUCCESS = 8,
    WS_PACKAGE_HEADER_TOTAL_LENGTH = 16,
    WS_BODY_PROTOCOL_VERSION_NORMAL = 0,
    WS_BODY_PROTOCOL_VERSION_BROTLI = 3,
    WS_HEADER_DEFAULT_VERSION = 1,
    WS_HEADER_DEFAULT_SEQUENCE = 1,
    WS_AUTH_OK = 0,
    WS_AUTH_TOKEN_ERROR = -101
};

struct UserInputT {
    uint64_t uid = 0;
    uint64_t roomID = 0;
    bool saveFile = false;
    bool debug = false;
};
struct RoomInfoT {
    uint64_t realRoomID = 0;
    uint64_t liveUpUID = 0;
};
struct PackageHeaderT {
    uint32_t totalSize = 0; // 包括Header的长度

    uint16_t headerLen = 0;
    uint16_t protocolVersion = 0;

    uint32_t operation = 0;
    uint32_t sequenceId = 0;
};

#endif //BILIBILILIVEPROTOCOL_DATASTRUCT_H
