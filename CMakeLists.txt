cmake_minimum_required(VERSION 3.13)
project(buu_tictactoe)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/Users/emilg1101/Desktop/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)
add_executable(buu_tictactoe main.cpp game/Display.h game/PlayerIOStream.h Structs.h console/ConsoleDisplay.cpp console/ConsoleDisplay.h game/Game.cpp game/Game.h game/player/Player.cpp game/player/Player.h game/player/ComputerPlayer.cpp game/player/ComputerPlayer.h game/storage/Saver.cpp game/storage/Saver.h game/algorithm/WinningCheckAlgorithm.cpp game/algorithm/WinningCheckAlgorithm.h game/CommandHandler.h gui/GraphicalDisplay.cpp gui/GraphicalDisplay.h)
target_link_libraries(buu_tictactoe sfml-graphics sfml-audio)
