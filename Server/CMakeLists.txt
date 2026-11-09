cmake_minimum_required(VERSION 4.1)
project(Server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
add_executable(Server
        main.cpp
        Receiver.cpp
        Receiver.h
        ../Message/Message.h
        ../Message/Message.cpp
)
target_link_libraries(Server PRIVATE ws2_32)