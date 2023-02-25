#include <WinSock2.h>
#include "Protocol/Protocol.h"
#include "ImWindow/ImWindow.h"
#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>

using std::string;
using std::runtime_error;


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

string requestURL(const string &Url) {
    HttpRequestT httpRequest {Url, "get"};
    HttpResponseT httpResponse;
    WinhttpAPI api(httpRequest, httpResponse);
    api.Request();
    return httpResponse.Body;
}

int main() {
    srand(time(nullptr));
    setbuf(stdout, nullptr);
    std::wcout.imbue(std::locale("chs"));

    try {
        ImWindow gui;
        gui.showInputWindow();

        std::cout << "A";

    } catch (runtime_error &error) {
        std::cout << "runtime error: " << error.what() << '\n';
    }




//    userWindow.getInput();
//
//    // 获取真实房间号
//    {
//        string responseBody = requestURL("https://api.live.bilibili.com/room/v1/Room/room_init?id=" + std::to_string(userWindow.userInput.roomID));
//        nlohmann::json nJson = nlohmann::json::parse(responseBody);
//
//        userWindow.roomInfo.realRoomID = nJson["data"]["room_id"];
//        userWindow.roomInfo.liveUpUID = nJson["data"]["uid"];
//        userWindow.setTitle("房间真实id号: " + std::to_string(userWindow.roomInfo.realRoomID) + " 开播up uid: " +
//                            std::to_string(userWindow.roomInfo.liveUpUID));
//    }
//
//    string danmuServerHost;
//    string danmuServerPort;
//    string danmuServerToken;
//    // 随机选取一个弹幕服务器
//    {
//        nlohmann::json nJson = nlohmann::json::parse(requestURL(
//                "https://api.live.bilibili.com/xlive/web-room/v1/index/getDanmuInfo?id=" + std::to_string(userWindow.roomInfo.realRoomID) + "&type=0"));
//        size_t index = rand() % nJson["data"]["host_list"].size();
//        danmuServerHost = nJson["data"]["host_list"][index]["host"];
//        danmuServerPort = to_string(nJson["data"]["host_list"][index]["wss_port"]);
//        danmuServerToken = nJson["data"]["token"];
//        if (userWindow.userInput.debug)
//            userWindow.pushMsg("选取弹幕服务器: " + danmuServerHost + ":" + danmuServerPort);
//    }
//
//    // websocket part
//    {
//        Protocol danmuProtocol(userWindow.userInput.uid, userWindow.roomInfo.realRoomID, danmuServerToken);
//        if (!ix::initNetSystem()) throw runtime_error("failed initNetSystem");
//
//        ix::WebSocket webSocket;
//        webSocket.setUrl("wss://" + danmuServerHost + ":" + danmuServerPort + "/sub");
//        webSocket.setPingInterval(25);
//        webSocket.setPingMessage(danmuProtocol.makePackage("[object Object]", WS_OP_HEARTBEAT), ix::SendMessageKind::Binary);
//
//        webSocket.setOnMessageCallback([&danmuProtocol, &webSocket,&userWindow](const ix::WebSocketMessagePtr &msg) {
//            if (msg->type == ix::WebSocketMessageType::Message) {
//                try {
//                    std::vector<nlohmann::json> vJson = danmuProtocol.parsePackageToJson(msg->str);
//                    for (auto &one: vJson) {
//                        userWindow.pushMsg(one);
//                    }
//                } catch (runtime_error &error) {
//                    std::cout << "runtime error: " << error.what() << '\n';
//                } catch (nlohmann::json::parse_error &error) {
//                    std::cout << "Json parse error: " << error.what() << '\n';
//                } catch (nlohmann::json::exception &exception) {
//                    std::cout << "Json exception error: " << exception.what() << '\n';
//                }
//            } else if (msg->type == ix::WebSocketMessageType::Open) {
//                std::cout << "socket reOpen\n";
//                if (!webSocket.sendBinary(danmuProtocol.makeAuthenticationPackage()).success)
//                    throw runtime_error("failed send auth package");
//            } else if (msg->type == ix::WebSocketMessageType::Error) {
//                std::cout << "Connection error: " << msg->errorInfo.reason << std::endl;
//                webSocket.close();
//            } else if (msg->type == ix::WebSocketMessageType::Close) {
//                std::cout << "WebSocket Close, code: " << msg->closeInfo.code << "close msg: " << msg->closeInfo.reason << '\n';
//            }
//        });
//        webSocket.start();
//
//        std::this_thread::sleep_for(std::chrono::hours {10});
//
//        webSocket.stop();
//        ix::uninitNetSystem();
//    }
    return 0;
}