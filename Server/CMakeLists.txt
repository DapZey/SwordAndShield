cmake_minimum_required(VERSION 3.27)
project(Server)

set(CMAKE_CXX_STANDARD 17)

add_executable(Server main.cpp
        ParsingUtils.cpp
        Network.cpp
        Player.cpp
        Protocol.cpp
        MathUtils.cpp
        MathUtils.h
        World.cpp
        World.h)
set(WINSOCK_LIBRARIES ws2_32)

# Link against Winsock
target_link_libraries(${PROJECT_NAME} ${WINSOCK_LIBRARIES})
set(CMAKE_EXE_LINKER_FLAGS "-static")