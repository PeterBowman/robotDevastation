# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/robotDevastation

find_package(YARP REQUIRED)

add_library(NetworkLib MockNetworkEventListener.hpp
                       MockNetworkEventListener.cpp
                       MockNetworkManager.hpp
                       MockNetworkManager.cpp
                       NetworkEventListener.hpp
                       NetworkManager.hpp
                       NetworkManager.cpp
                       YarpNetworkManager.hpp
                       YarpNetworkManager.cpp)

target_include_directories(NetworkLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                             ${YARP_INCLUDE_DIRS})

target_link_libraries(NetworkLib PUBLIC YARP::YARP_OS
                                        MentalMapLib)

target_link_libraries(NetworkLib PRIVATE UtilsLib)
