cmake_minimum_required(VERSION 3.13)
project(buu_tictactoe)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(buu_tictactoe main.cpp game/Display.h game/PlayerIOStream.h Structs.h console/ConsoleDisplay.cpp console/ConsoleDisplay.h game/Game.cpp game/Game.h game/player/FirstPlayer.cpp game/player/FirstPlayer.h game/player/SecondPlayer.cpp game/player/SecondPlayer.h game/player/ComputerPlayer.cpp game/player/ComputerPlayer.h game/algorithm/WinningCheckAlgorithm.cpp game/algorithm/WinningCheckAlgorithm.h)