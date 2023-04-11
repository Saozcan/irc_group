cmake_minimum_required(VERSION 3.24)
project(irc_group)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/channel)
include_directories(src/command)
include_directories(src/command/commands)
include_directories(src/server)
include_directories(src/user)
include_directories(src/utility)

add_executable(irc_group
        src/channel/Channel.cpp
        src/channel/Channel.hpp
        src/command/commands/Join.cpp
        src/command/commands/Join.hpp
        src/command/commands/Nick.cpp
        src/command/commands/Nick.hpp
        src/command/commands/Pass.cpp
        src/command/commands/Pass.hpp
        src/command/commands/User.cpp
        src/command/commands/User.hpp
        src/command/ACommand.cpp
        src/command/ACommand.hpp
        src/command/CommandExecuter.cpp
        src/command/CommandExecuter.hpp
        src/server/Server.cpp
        src/server/Server.hpp
        src/user/NormalUser.cpp
        src/user/NormalUser.hpp
        src/utility/Utility.cpp
        src/utility/Utility.hpp
        src/irc.hpp
        src/main.cpp src/command/commands/Mode.cpp src/channel/ChannelBook.cpp src/command/commands/Help.cpp src/command/commands/Privmsg.hpp src/command/commands/Privmsg.cpp src/command/commands/Kick.hpp src/command/commands/Kick.cpp src/command/commands/Notice.hpp src/command/commands/Notice.cpp src/command/commands/Ping.cpp src/IRC_COMMAND.hpp src/command/commands/Cap.hpp src/command/commands/Cap.cpp)
