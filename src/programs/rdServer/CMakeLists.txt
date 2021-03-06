# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/robotDevastation

option(ENABLE_rdServer "Choose if you want to compile rdServer" ON)

if(ENABLE_rdServer)

# Find YARP.  Point the YARP_DIR environment variable at your build.
find_package(YARP REQUIRED)

# Set up our main executable.
add_executable(rdServer main.cpp)

target_include_directories(rdServer PUBLIC ${YARP_INCLUDE_DIRS})

target_link_libraries(rdServer YARP::YARP_init
                               YARP::YARP_OS
                               ServerLib
                               UtilsLib)

if(WIN32)
    target_compile_definitions(rdServer PUBLIC SDL_MAIN_HANDLED)
endif()

install(TARGETS rdServer DESTINATION ${CMAKE_INSTALL_BINDIR})

# Organize targets in folders (Visual Studio)
set_target_properties(rdServer PROPERTIES FOLDER Programs)

endif() # ENABLE_rdServer
