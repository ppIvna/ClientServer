cmake_minimum_required(VERSION 4.1)
project(Client)

set(CMAKE_CXX_STANDARD 20)

add_executable(Client main.cpp
        Sender.cpp
        Sender.h
        ../Message/Message.cpp
        ../Message/Message.h
        )

if(WIN32)
    target_link_libraries(Client PRIVATE ws2_32)
endif()