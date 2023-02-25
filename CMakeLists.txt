cmake_minimum_required(VERSION 3.21)

set(CMAKE_TOOLCHAIN_FILE D:/Clion/vcpkg/scripts/buildsystems/vcpkg.cmake)

project(bilibiliLiveRecorder)

set(CMAKE_CXX_STANDARD 17)

include_directories(D:/Clion/Project/Winhttp_SimpleAPI)
include_directories(D:/Clion/Project/Remote/IXWebSocket)

find_package(imgui CONFIG REQUIRED)
find_package(unofficial-brotli CONFIG REQUIRED)
find_package(ZLIB)
find_package(OpenSSL REQUIRED)

add_executable(bilibiliLiveRecorder
        main.cpp
        Protocol/Protocol.cpp
        Protocol/Protocol.h
        DataStruct/DataStruct.h
        ImWindow/ImWindow.cpp
        ImWindow/ImWindow.h)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    target_link_libraries(bilibiliLiveRecorder D:/Clion/Project/Winhttp_SimpleAPI/cmake-build-debug/Winhttp_SimpleAPI.lib)
    target_link_libraries(bilibiliLiveRecorder D:/Clion/Project/Remote/IXWebSocket/cmake-build-debug/ixwebsocket.lib)
else ()
    target_link_libraries(bilibiliLiveRecorder D:/Clion/Project/Winhttp_SimpleAPI/cmake-build-release/Winhttp_SimpleAPI.lib)
    #    target_link_libraries(bilibiliLiveRecorder D:/Clion/Project/Remote/IXWebSocket/cmake-build-release/ixwebsocket.lib)
endif ()
target_link_libraries(bilibiliLiveRecorder imgui::imgui)
target_link_libraries(bilibiliLiveRecorder d3d11)
target_link_libraries(bilibiliLiveRecorder OpenSSL::SSL)
target_link_libraries(bilibiliLiveRecorder unofficial::brotli::brotlidec)
target_link_libraries(bilibiliLiveRecorder ZLIB::ZLIB)
target_link_libraries(bilibiliLiveRecorder ws2_32)
target_link_libraries(bilibiliLiveRecorder crypt32)
target_link_libraries(bilibiliLiveRecorder shlwapi)
