#ifndef BILIBILILIVEPROTOCOL_DATASTRUCT_H
#define BILIBILILIVEPROTOCOL_DATASTRUCT_H

#include <cstdint>



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


#endif //BILIBILILIVEPROTOCOL_DATASTRUCT_H
