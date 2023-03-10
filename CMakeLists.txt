cmake_minimum_required(VERSION 3.24)
project(irc_group)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(irc_group
        src/command/ACommand.hpp
        src/user/AUser.hpp
        src/channel/Channel.hpp
        src/command/CommandExecuter.hpp
        src/command/Commands.hpp
        main.cpp
        src/user/NormalUser.hpp
        src/server/Server.hpp src/user/AUser.cpp src/user/NormalUser.cpp src/server/Server.cpp src/channel/Channel.cpp src/command/ACommand.cpp src/command/CommandExecuter.cpp)
