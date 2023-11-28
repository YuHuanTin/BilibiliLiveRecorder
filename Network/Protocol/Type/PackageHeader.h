//
// Created by YuHuanTin on 2023/11/28.
//

#ifndef BILIBILILIVEPROTOCOL_PACKAGEHEADER_H
#define BILIBILILIVEPROTOCOL_PACKAGEHEADER_H

#include <cstdint>

struct PackageHeader {
    uint32_t totalLength;

    uint16_t headerLength;
    uint16_t protocalVersion;

    uint32_t operation;
    uint32_t sequeceId;
};


#endif //BILIBILILIVEPROTOCOL_PACKAGEHEADER_H
