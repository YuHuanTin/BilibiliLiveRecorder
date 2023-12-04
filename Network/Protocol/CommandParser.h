//
// Created by YuHuanTin on 2023/12/4.
//

#ifndef BILIBILILIVEPROTOCOL_COMMANDPARSE_H
#define BILIBILILIVEPROTOCOL_COMMANDPARSE_H


#include <string>
#include <expected>

namespace CommandParse {

    std::expected<std::string, std::string> parse(const std::string &DataToParse);

}


#endif //BILIBILILIVEPROTOCOL_COMMANDPARSE_H
