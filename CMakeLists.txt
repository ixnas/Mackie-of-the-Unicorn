cmake_minimum_required(VERSION 3.21)

# Compile universal binary on macOS
option(BUILD_UNIVERSAL "Build macOS univeral binary" ON)
if (APPLE)
    if (BUILD_UNIVERSAL)
        set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
    endif()
endif ()

# Version labeling
execute_process(
        COMMAND git describe --always
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        OUTPUT_VARIABLE GIT_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
configure_file(${CMAKE_SOURCE_DIR}/src/git_version.h.in ${CMAKE_SOURCE_DIR}/src/git_version.h @ONLY)

# Set up project
project(Mackie_of_the_Unicorn)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

# Options
option(BUILD_DOC "Build documentation" ON)
option(BUILD_TESTS "Build tests" ON)
option(BUILD_GUI "Build graphical user interface" ON)

# Setup dependencies
if (APPLE)
    find_library(COREMIDI CoreMidi "/")
    find_library(COREFOUNDATION CoreFoundation "/")
    set(RTMIDI_API_CORE ON)
    set(OS_FLAGS "-framework CoreFoundation -framework CoreMIDI -framework CoreAudio")
elseif (MINGW)
    set(OS_FLAGS "-static-libgcc -static-libstdc++ -static -mwindows" winmm.lib)
else ()
    set(OS_FLAGS "")
endif ()
set(RAPIDJSON_BUILD_TESTS off)
set(RAPIDJSON_BUILD_EXAMPLES off)
set(RAPIDJSON_BUILD_DOC off)
set(RTMIDI_BUILD_TESTING off)
set(RTMIDI_BUILD_STATIC_LIBS on)
set(RAPIDJSON_ENABLE_INSTRUMENTATION_OPT off)
set(wxBUILD_PRECOMP OFF)
set(wxBUILD_SHARED OFF)

# Include dependencies
find_package(CURL REQUIRED)
add_subdirectory(${CMAKE_SOURCE_DIR}/ext/rapidjson)
add_subdirectory(${CMAKE_SOURCE_DIR}/ext/rtmidi)
if (BUILD_TESTS)
    add_subdirectory(${CMAKE_SOURCE_DIR}/ext/googletest)
endif ()
if (BUILD_GUI)
    add_subdirectory(${CMAKE_SOURCE_DIR}/ext/wxWidgets)
    set(WX_LIBRARIES wx::base wx::core)
    set(MAIN_EXECUTABLE ${CMAKE_SOURCE_DIR}/src/GUI/main.cpp)
else()
    set(WX_LIBRARIES "")
    set(MAIN_EXECUTABLE ${CMAKE_SOURCE_DIR}/src/Console/main.cpp)
endif()

# Sources
file(GLOB_RECURSE sources src/*.cpp src/*.h)
list(FILTER sources EXCLUDE REGEX ".*main\\.cpp$")
list(APPEND sources ${MAIN_EXECUTABLE})

# Sources except main, for tests
file(GLOB_RECURSE test_sources src/*.cpp src/*.h)
list(FILTER test_sources EXCLUDE REGEX ".*main\\.cpp$")

# Test sources
file(GLOB_RECURSE unit_tests test/unit/*.cpp test/unit/*.h test/fakes/*.h)
file(GLOB_RECURSE integration_tests test/integration/*.cpp test/integration/*.h test/fakes/*.h)

# Main executable
add_executable(Mackie_of_the_Unicorn ${sources})
add_dependencies(Mackie_of_the_Unicorn rtmidi ${WX_LIBRARIES})
target_include_directories(Mackie_of_the_Unicorn PUBLIC ext/rapidjson/include rtmidi ${CURL_INCLUDE_DIR})
target_link_libraries(Mackie_of_the_Unicorn ${CMAKE_BINARY_DIR}/ext/rtmidi/librtmidi.a ${CURL_LIBRARIES} ${WX_LIBRARIES} ${OS_FLAGS})

# Tests
if (BUILD_TESTS)
    enable_testing()

    # Unit tests
    add_executable(Unit_Tests ${test_sources} ${unit_tests})
    add_dependencies(Unit_Tests rtmidi)
    target_include_directories(Unit_Tests PUBLIC ext/rapidjson/include rtmidi ${CURL_INCLUDE_DIR})
    target_link_libraries(Unit_Tests gtest_main gmock ${CMAKE_BINARY_DIR}/ext/rtmidi/librtmidi.a ${CURL_LIBRARIES} ${OS_FLAGS})
    target_compile_definitions(Unit_Tests PRIVATE TESTING=1)

    # Integration tests
    add_executable(Integration_Tests ${test_sources} ${integration_tests})
    add_dependencies(Integration_Tests rtmidi)
    target_include_directories(Integration_Tests PUBLIC rapidjson/include rtmidi ${CURL_INCLUDE_DIR})
    target_link_libraries(Integration_Tests gtest_main gmock ${CMAKE_BINARY_DIR}/ext/rtmidi/librtmidi.a ${CURL_LIBRARIES} ${OS_FLAGS})
    target_compile_definitions(Integration_Tests PRIVATE TESTING=1)
endif ()

# Documentation
if (BUILD_DOC)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        # set input and output files
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

        # request to configure the file
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

        # note the option ALL which allows to build the docs together with the application
        add_custom_target(doc ALL
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                COMMENT "Generating API documentation with Doxygen"
                VERBATIM)
    else (DOXYGEN_FOUND)
        message("Doxygen need to be installed to generate the doxygen documentation")
    endif (DOXYGEN_FOUND)
endif ()
