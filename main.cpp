
//void showDanmu(std::vector<nlohmann::json> &vJson) {
//    for (int i = 0; i < vJson.size(); ++i) {
//
//        if (vJson[i].contains("/cmd"_json_pointer)) {
//            if (vJson[i].at("/cmd"_json_pointer) == "DANMU_MSG") {
//                std::stringstream ss;
//                string guardType[] = {{u8"观众"},
//                                      {u8"总督"},
//                                      {u8"提督"},
//                                      {u8"舰长"}};
//
//                string msg = vJson[i].at("/info/1"_json_pointer).is_null() ? "" : vJson[i].at("/info/1"_json_pointer);
//                string userName = vJson[i].at("/info/2/1"_json_pointer);
//                int64_t userID = vJson[i].at("/info/2/0"_json_pointer);
//
//                string fansMedalLabel = u8"未佩戴牌子";
//                string fansMedalAnchorUsername = u8"未佩戴牌子";
//                uint32_t fansMedalLevel = 0;
//                uint32_t guardTypeIndex = 0;
//                uint64_t fansMedalAnchorId = 0;
//                if (!vJson[i].at("/info/3"_json_pointer).empty()) {
//                    fansMedalLabel = vJson[i].at("/info/3/1"_json_pointer);
//                    fansMedalLevel = vJson[i].at("/info/3/0"_json_pointer);
//                    fansMedalAnchorUsername = vJson[i].at("/info/3/2"_json_pointer);
//                    fansMedalAnchorId = vJson[i].at("/info/3/12"_json_pointer);
//                    guardTypeIndex = vJson[i].at("/info/3/10"_json_pointer);
//                }
//                if (gEnv.debug) {
//                    ss << "[" << fansMedalAnchorUsername << "(uid:" << fansMedalAnchorId << ")]<" << fansMedalLabel << " " << fansMedalLevel << ">["
//                       << guardType[guardTypeIndex] << "] " << userName << "(uid:" << userID << ") : " << msg;
//                } else {
//                    ss << "<" << fansMedalLabel << " " << fansMedalLevel << ">[" << guardType[guardTypeIndex] << "] " << userName << "(uid:" << userID << ") : "
//                       << msg;
//                }
//
//
//                std::wcout << CodeCvt::StrToWstr(ss.str(), CP_UTF8) << '\n';
//                if (gEnv.saveFile) {
//                    fwrite(ss.str().c_str(), 1, ss.str().length(), gEnv.fp);
//                    fflush(gEnv.fp);
//                }
//            }
//        } else if (vJson[i].contains("/popularValue"_json_pointer)) {
//            std::cout << "人气值: " << vJson[i]["popularValue"] << '\n';
//        } else if (vJson[i].contains("/code"_json_pointer)) {
//            if (vJson[i]["code"] == WS_AUTH_OK)
//                std::cout << "连接成功\n";
//            else if (vJson[i]["code"] == WS_AUTH_TOKEN_ERROR)
//                throw runtime_error("Token错误");
//            else throw runtime_error("未知错误");
//        } else throw runtime_error("未知分支");
//
//    }
//
//}



#include <cstdio>
#include <print>
#include <boost/locale.hpp>
#include "Utils/Interface.h"
#include "Network/Protocol/Protocol.h"

int main() {
    setbuf(stdout, nullptr);


    std::unique_ptr<WSSClient> startResult = Interface::start(213, [&startResult](const ix::WebSocketMessagePtr &msg) {
        switch (msg->type) {
            case ix::WebSocketMessageType::Message: {
                std::println("recv {} bytes", msg->str.size());

                std::vector<uint8_t> bufffer(msg->str.begin(), msg->str.end());
                auto vecParseData = Protocol::parse_packages(bufffer);


                std::println("parse message count: {}", vecParseData.size());
                for (const auto &str: vecParseData) {

                    Interface::parseCommandData(str);

                    /// conv string from utf-8 to gbk
                    auto str2 = boost::locale::conv::from_utf(str, "GBK");

                    std::println("{}", str2);
                }
                break;
            }
            case ix::WebSocketMessageType::Open: {
                std::println("Connected");
                startResult->sendAuthentication();
                break;
            }
            case ix::WebSocketMessageType::Close: {
                std::println("Disconnected");
                break;
            }
            case ix::WebSocketMessageType::Error: {
                std::println("Error");
                break;
            }
            case ix::WebSocketMessageType::Pong: {
                std::println("Pong");
                break;
            }
            case ix::WebSocketMessageType::Ping: {
                std::println("Ping");
                break;
            }
        }
    });

    std::this_thread::sleep_for(std::chrono::hours(10));
    startResult->stop();
    
    return 0;

}