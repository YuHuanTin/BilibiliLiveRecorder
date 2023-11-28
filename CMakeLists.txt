cmake_minimum_required(VERSION 3.26)


project(bilibiliLiveRecorder)

set(CMAKE_CXX_STANDARD 23)


find_package(cpr CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ixwebsocket CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(unofficial-brotli CONFIG REQUIRED)


link_libraries(unofficial::brotli::brotlidec)
link_libraries(nlohmann_json::nlohmann_json)
link_libraries(ixwebsocket::ixwebsocket)
link_libraries(imgui::imgui)
link_libraries(cpr::cpr)


add_definitions(-DOUTPUT_INFO=1)


add_executable(bilibiliLiveRecorder
        main.cpp
        UtilsHelper/Interface.cpp
        UtilsHelper/Interface.h
        UtilsHelper/ExpectionHelper/ExpectionHelper.cpp
        UtilsHelper/ExpectionHelper/ExpectionHelper.h
        Network/WS/WSClient.cpp
        Network/WS/WSClient.h
        Network/Protocol/ProtocolPackageMaker.cpp
        Network/Protocol/ProtocolPackageMaker.h
        Network/Protocol/Type/OperatorType.h
        Network/Protocol/Type/PackageHeader.h
)

