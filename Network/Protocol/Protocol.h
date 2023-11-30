#ifndef BILIBILILIVEPROTOCOL_PROTOCOL_H
#define BILIBILILIVEPROTOCOL_PROTOCOL_H


#include <string>
#include <vector>
#include <expected>


namespace Protocol {
    /**
     * make a authentication package
     * 
     * @return 
     */
    [[nodiscard]] std::vector<uint8_t>
    make_authentication_package(uint64_t Uid, uint64_t RoomId, const std::string &Token, const std::string &UserCookie);

    /**
     * make a heartbeat package
     * throw exception if make failed
     * 
     * @return 
     */
    [[nodiscard]] std::vector<uint8_t> make_heartbeat_package();


    std::vector<std::string> parse_packages(std::vector<uint8_t> &DataToParse);
}


#endif //BILIBILILIVEPROTOCOL_PROTOCOL_H
