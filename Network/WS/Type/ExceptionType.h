//
// Created by YuHuanTin on 2023/11/29.
//

#ifndef BILIBILILIVEPROTOCOL_EXCEPTIONTYPE_H
#define BILIBILILIVEPROTOCOL_EXCEPTIONTYPE_H


#include <exception>

namespace ExpectionType {
    struct Net_Init_Failed : std::exception {
        [[nodiscard]] const char *what() const override {
            return "net init failed";
        }
    };

    struct Net_Uninit_Failed : std::exception {
        [[nodiscard]] const char *what() const override {
            return "net uninit failed";
        }
    };
}

#endif //BILIBILILIVEPROTOCOL_EXCEPTIONTYPE_H
