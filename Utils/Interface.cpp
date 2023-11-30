//
// Created by YuHuanTin on 2023/11/19.
//

#include "Interface.h"

#include <print>
#include <random>
#include <string_view>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "ExpectionHelper/ExpectionHelper.h"

struct LiveServer {
    std::string Host;
    uint32_t Port;
    std::string Token;
};

auto get_random_value(uint32_t Min, uint32_t Max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<uint32_t> dist(Min, Max);
    return dist(mt);
}

auto get_room_id(uint64_t RoomID) {
    try {
        cpr::Url url{"https://api.live.bilibili.com/room/v1/Room/room_init"};
        cpr::Parameters params{
                {"id", std::to_string(RoomID)}
        };
        auto response = cpr::Get(url, params);

        nlohmann::json json = nlohmann::json::parse(response.text);
        uint64_t trueRoomID = json["data"]["room_id"];
        uint64_t liveUpUID = json["data"]["uid"];
#if OUTPUT_INFO
        std::println("房间真实id号: {} 开播up uid: {}", trueRoomID, liveUpUID);
#endif
        return trueRoomID;
    } catch (std::exception &Exception) {
        ExpectionHelper::dumpExpection("获取房间真实id号失败", Exception);
        throw Exception;
    }
}

auto get_live_server(uint64_t RoomID) {
    try {
        cpr::Url url{"https://api.live.bilibili.com/xlive/web-room/v1/index/getDanmuInfo"};
        cpr::Parameters params{
                {"id",   std::to_string(RoomID)},
                {"type", "0"}
        };

        auto response = cpr::Get(url, params);

        nlohmann::json json = nlohmann::json::parse(response.text);
        auto randomIndex = get_random_value(0, json["data"]["host_list"].size() - 1);

        return LiveServer{
                .Host = json["data"]["host_list"][randomIndex]["host"],
                .Port = json["data"]["host_list"][randomIndex]["wss_port"],
                .Token = json["data"]["token"]
        };
    } catch (std::exception &Exception) {
        ExpectionHelper::dumpExpection("获取弹幕服务器失败", Exception);
        throw Exception;
    }
}

namespace Interface {
    StartResult start(uint64_t RoomID) {
        try {
            auto trueRoomID = get_room_id(RoomID);
            auto liveServer = get_live_server(trueRoomID);


            std::println("弹幕服务器: {}:{}", liveServer.Host, liveServer.Port);


            auto websocket = std::make_unique<WSClient>();

            websocket->setUrl("wss://" + liveServer.Host + ":" + std::to_string(liveServer.Port) + "/sub");
//                    .setPingInterval(25)
//                    .setPingMessage(Protocol::make_heartbeat_package());


            return {std::move(websocket), trueRoomID, liveServer.Token};
        } catch (std::exception &Exception) {
            ExpectionHelper::dumpExpection("启动失败", Exception, false);
        }
    }
} // Interface