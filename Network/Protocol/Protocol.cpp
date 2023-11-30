

#include "Protocol.h"

#include <nlohmann/json.hpp>
#include "PackageMaker/PackageMaker.h"

namespace Protocol {
    std::vector<uint8_t>
    make_authentication_package(uint64_t Uid, uint64_t RoomId, const std::string &Token, const std::string &UserCookie) {

        /// make authentication package body
        std::string jsonStr;
        try {
            /**
                {
                    "uid": xxxxxxxxxx,
                    "roomid": xxxxxxxxxx,
                    "protover": 3,
                    "buvid": "?",
                    "platform": "web",
                    "type": 2,
                    "key": ""
                }
            */
            nlohmann::json nJson = {{"uid",      Uid},
                                    {"roomid",   RoomId},
                                    {"protover", 3},
                                    {"platform", "web"},
                                    {"type",     2},
                                    {"key",      Token},
                                    {"buvid",    UserCookie}};
            jsonStr = std::move(to_string(nJson));
        } catch (nlohmann::json::type_error &error) {
            throw std::runtime_error("unknow error to make authentication body");
        }


        /// make authentication package
        auto authMessageResult = PackageMaker::make(jsonStr, OperatorType::WS_OP_USER_AUTHENTICATION);
        if (!authMessageResult) {
            throw std::runtime_error("unknow error to make authentication package");
        }
        return authMessageResult.value();
    }

    std::vector<uint8_t> make_heartbeat_package() {
        static const std::string str = "[object Object]";
        auto authMessageResult = PackageMaker::make(str, OperatorType::WS_OP_HEARTBEAT);

        if (!authMessageResult) {
            throw std::runtime_error("unknow error to make heartbeat package");
        }
        return authMessageResult.value();
    }

    std::vector<std::string> parse_packages(std::vector<uint8_t> &DataToParse) {
        auto parseResult = PackageMaker::parse(DataToParse);
        if (!parseResult) {
            throw std::runtime_error("unknow error to parse packages");
        }
        return parseResult.value();
    }
}
