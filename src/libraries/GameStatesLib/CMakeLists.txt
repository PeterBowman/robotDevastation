# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/robotDevastation

add_library(GameStatesLib DeadState.hpp
                          DeadState.cpp
                          GameState.hpp
                          GameState.cpp
                          InitState.hpp
                          InitState.cpp)

target_include_directories(GameStatesLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(GameStatesLib PUBLIC UtilsLib
                                           StateMachineLib
                                           InputLib
                                           NetworkLib
                                           ImageLib
                                           MentalMapLib
                                           RobotLib
                                           MusicLib
                                           UserInterfaceLib)
