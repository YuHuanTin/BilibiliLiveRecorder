//
// Created by YuHuanTin on 2023/12/4.
//

#include "CommandParser.h"
#include <map>
#include <nlohmann/json.hpp>


std::map<std::string, std::function<std::string()>> CommandMap
        {
                {"LIVE_INTERACTIVE_GAME",        []() {
                    return "LIVE_INTERACTIVE_GAME";
                }
                },
                {"LIVE_INTERACTIVE_GAME_RESULT", []() {
                    return "";
                }
                },
                {"INTERACT_WORD",                []() {
                    /// µ¯Ä»
                    return "";
                }}
        };

namespace CommandParse {
    std::expected<std::string, std::string> parse(const std::string &DataToParse) {
        nlohmann::json json;
        try {
            json = std::move(nlohmann::json::parse(DataToParse));


            /// dispatch it with cmd
            return CommandMap[json["cmd"]]();
        } catch (std::exception &Exception) {
            return std::unexpected<std::string>(Exception.what());
        }
    }
}