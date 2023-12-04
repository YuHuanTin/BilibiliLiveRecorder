cmake_minimum_required(VERSION 3.26)


project(bilibiliLiveRecorder)

set(CMAKE_CXX_STANDARD 23)


find_package(cpr CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ixwebsocket CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(unofficial-brotli CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS locale)

link_libraries(Boost::locale)
link_libraries(unofficial::brotli::brotlidec)
link_libraries(nlohmann_json::nlohmann_json)
link_libraries(ixwebsocket::ixwebsocket)
link_libraries(imgui::imgui)
link_libraries(cpr::cpr)


add_definitions(-DOUTPUT_INFO=1)


add_executable(bilibiliLiveRecorder
        main.cpp
        Utils/Interface.cpp
        Utils/Interface.h
        Utils/ExpectionHelper/ExpectionHelper.cpp
        Utils/ExpectionHelper/ExpectionHelper.h
        Network/WS/Client/WebSocketCore.cpp
        Network/WS/Client/WebSocketCore.h
        Network/Protocol/Protocol.h
        Network/Protocol/Protocol.cpp
        Network/Protocol/PackageMaker/PackageMaker.h
        Network/Protocol/PackageMaker/PackageMaker.cpp
        Network/Protocol/Type/OperatorType.h
        Network/Protocol/Type/PackageHeader.h
        Network/WS/Type/ExceptionType.h
        Network/WS/WSSClient.cpp
        Network/WS/WSSClient.h
        Network/Protocol/CommandParse.cpp
        Network/Protocol/CommandParser.h
)

