//
// Created by YuHuanTin on 2023/11/28.
//

#ifndef BILIBILILIVEPROTOCOL_PROTOCOLPACKAGE_H
#define BILIBILILIVEPROTOCOL_PROTOCOLPACKAGE_H


#include <string>
#include <vector>
#include <expected>

#include "Type/OperatorType.h"
#include "Type/PackageHeader.h"

namespace ProtocolPackage {
    /**
     * to make a protocol package
     * 
     * @param DataToMake 
     * @param Operator 
     * @return 
     */
    std::expected<std::vector<uint8_t>, std::string> make(const std::string &DataToMake, OperatorType Operator);

    /**
     * this is a recursive function
     * get protocol package body with decode
     * 
     * @param DataToParse 
     * @return 
     */
    std::expected<std::vector<std::string>, std::string> parse(std::vector<uint8_t> &DataToParse);
}


#endif //BILIBILILIVEPROTOCOL_PROTOCOLPACKAGE_H
