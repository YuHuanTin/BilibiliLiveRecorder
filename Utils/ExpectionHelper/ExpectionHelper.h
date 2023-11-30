//
// Created by YuHuanTin on 2023/11/19.
//

#ifndef BILIBILILIVEPROTOCOL_EXPECTIONHELPER_H
#define BILIBILILIVEPROTOCOL_EXPECTIONHELPER_H


#include <string>

namespace ExpectionHelper {
    void dumpExpection(std::exception &Exception, bool With_Stack = true);

    void dumpExpection(const char *Additional, std::exception &Exception, bool With_Stack = true);
}


#endif //BILIBILILIVEPROTOCOL_EXPECTIONHELPER_H
