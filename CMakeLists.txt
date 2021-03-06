# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/robotDevastation

cmake_minimum_required(VERSION 2.8.11)

project(robotDevastation)

include(CMakeDependentOption)

if(MSVC)
    message(STATUS "Running on windows")    
    set(CMAKE_DEBUG_POSTFIX "d")
endif()

# Let the user specify a configuration (only single-config generators).
if(NOT CMAKE_CONFIGURATION_TYPES)
    # Possible values.
    set(_configurations Debug Release MinSizeRel RelWithDebInfo)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${_configurations})

    foreach(_conf ${_configurations})
        set(_conf_string "${_conf_string} ${_conf}")
    endforeach()

    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY HELPSTRING
                 "Choose the type of build, options are:${_conf_string}")

    if(NOT CMAKE_BUILD_TYPE)
        # Encourage the user to specify build type.
        message(STATUS "Setting build type to 'Release' as none was specified.")
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY VALUE Release)
    endif()
endif()

# Standard installation directories.
include(GNUInstallDirs)

# Control where libraries and executables are placed during the build.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})

# Pick up our scripts - they are all in the /cmake subdirectory
set(RD_MODULE_DIR ${CMAKE_SOURCE_DIR}/cmake)

list(APPEND CMAKE_MODULE_PATH ${RD_MODULE_DIR}
                              ${RD_MODULE_DIR}/find-modules)

option(ENABLE_coverage "Choose if you want to enable coverage" OFF)

if(ENABLE_coverage)
    # List supported compilers.
    if(CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    endif()
endif()

# let CMake organize projects in folders (in IDEs that support this)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# add main contents
add_subdirectory(share)
add_subdirectory(src)
add_subdirectory(test)

# generate documentation
find_package(Doxygen QUIET)

cmake_dependent_option(GENERATE_doc_html "Choose if you want to generate HTML documentation through Doxygen" OFF
                       DOXYGEN_FOUND OFF)

if(GENERATE_doc_html)
    if(CMAKE_GENERATOR MATCHES "^(Visual Studio|Xcode)")
        set(_dox DOX)
    else()
        set(_dox dox)
    endif()

    add_custom_target(${_dox}
                      COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/doc/Doxyfile
                      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/doc
                      COMMENT "Generating doxygen documentation"
                      SOURCES ${CMAKE_SOURCE_DIR}/doc/Doxyfile)

    set_property(TARGET ${_dox} PROPERTY FOLDER CMakePredefinedTargets)

    install(DIRECTORY ${CMAKE_SOURCE_DIR}/doc/html
            DESTINATION ${CMAKE_INSTALL_DOCDIR})
endif()

# uninstall target
include(AddUninstallTarget)
