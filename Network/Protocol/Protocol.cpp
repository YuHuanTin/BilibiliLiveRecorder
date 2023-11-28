#include "Protocol.h"



// 解析协议包头
PackageHeaderT parsePackageHeader(const char *Buf) {
    PackageHeaderT packageHeader;
    memcpy(&packageHeader, Buf, WSMsgTypeE::WS_PACKAGE_HEADER_TOTAL_LENGTH);
    packageHeader.totalSize = ntohl(packageHeader.totalSize);
    packageHeader.headerLen = ntohs(packageHeader.headerLen);
    packageHeader.protocolVersion = ntohs(packageHeader.protocolVersion);
    packageHeader.operation = ntohl(packageHeader.operation);
    packageHeader.sequenceId = ntohl(packageHeader.sequenceId);
    return packageHeader;
}

// 构造协议包头
PackageHeaderT makePackageHeader(const std::string &Buf, WSMsgTypeE WsMsg) {
    PackageHeaderT packageHeader;
    packageHeader.totalSize = htonl(WSMsgTypeE::WS_PACKAGE_HEADER_TOTAL_LENGTH + Buf.length());
    packageHeader.headerLen = htons(WSMsgTypeE::WS_PACKAGE_HEADER_TOTAL_LENGTH);
    packageHeader.protocolVersion = htons(WS_HEADER_DEFAULT_VERSION);
    packageHeader.operation = htonl((uint32_t) WsMsg);
    packageHeader.sequenceId = htonl(WS_HEADER_DEFAULT_SEQUENCE);
    return packageHeader;
}

// 解析包
vector <nlohmann::json> Protocol::parsePackageToJson(const std::string &Buf) {
    vector<nlohmann::json> vJson;
    for (uint32_t scanPos = 0; scanPos < Buf.length();) {
        PackageHeaderT packageHeader = parsePackageHeader(Buf.c_str() + scanPos);
        if (packageHeader.operation == WS_OP_CONNECT_SUCCESS) {
            vJson.push_back(nlohmann::json::parse(std::string{Buf.c_str() + WSMsgTypeE::WS_PACKAGE_HEADER_TOTAL_LENGTH,
                                                          packageHeader.totalSize -
                                                          WSMsgTypeE::WS_PACKAGE_HEADER_TOTAL_LENGTH
            }));
        } else if (packageHeader.operation == WS_OP_HEARTBEAT_REPLY) {
            // 心跳包返回人气值
            uint32_t popularValue = *(uint32_t *) (Buf.c_str() + WS_PACKAGE_HEADER_TOTAL_LENGTH);
            return {{{"popularValue", ntohl(popularValue)}}};
        } else if (packageHeader.operation == WS_OP_MESSAGE) {
            try {
                if (packageHeader.protocolVersion == WS_BODY_PROTOCOL_VERSION_BROTLI) {
                    vJson = parsePackageToJson(decompress(
                            {Buf.c_str() + scanPos + WSMsgTypeE::WS_PACKAGE_HEADER_TOTAL_LENGTH,
                             packageHeader.totalSize - WSMsgTypeE::WS_PACKAGE_HEADER_TOTAL_LENGTH
                            }));
                } else if (packageHeader.protocolVersion == WS_BODY_PROTOCOL_VERSION_NORMAL) {
                    vJson.push_back(nlohmann::json::parse(
                            std::string{Buf.c_str() + scanPos + WSMsgTypeE::WS_PACKAGE_HEADER_TOTAL_LENGTH,
                                    packageHeader.totalSize - WSMsgTypeE::WS_PACKAGE_HEADER_TOTAL_LENGTH
                            }));
                }
            } catch (runtime_error &error) {
                cout << "runtime error: " << error.what() << '\n';
            } catch (nlohmann::json::parse_error &error) {
                cout << "Json parse error: " << error.what() << '\n';
            }
        }
        scanPos += packageHeader.totalSize;
    }
    return vJson;
}

// 构造包
std::string Protocol::makePackage(const std::string &Buf, WSMsgTypeE WsMsg) {
    PackageHeaderT packageHeader = makePackageHeader(Buf, WsMsg);

    std::string str(WSMsgTypeE::WS_PACKAGE_HEADER_TOTAL_LENGTH + Buf.length(), 0);
    memcpy((void *) str.c_str(), (void *) &packageHeader, WSMsgTypeE::WS_PACKAGE_HEADER_TOTAL_LENGTH);
    memcpy((void *) (str.c_str() + WSMsgTypeE::WS_PACKAGE_HEADER_TOTAL_LENGTH), Buf.c_str(), Buf.length());
    return str;
}

// 构造验证包
std::string Protocol::makeAuthenticationPackage() {
    nlohmann::json nJson = {{"uid",      uid},
                            {"roomid",   realRoomID},
                            {"protover", 3},
                            {"platform", "web"},
                            {"type",     2},
                            {"key",      token}};
    return makePackage(to_std::string(nJson), WSMsgTypeE::WS_OP_USER_AUTHENTICATION);
}
