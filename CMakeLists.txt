cmake_minimum_required(VERSION 3.21)

execute_process(
        COMMAND git log -1 --format=%h
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        OUTPUT_VARIABLE GIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
        COMMAND git branch --show-current
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        OUTPUT_VARIABLE GIT_BRANCH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(GIT_VERSION ${GIT_BRANCH}-${GIT_HASH})

project(Mackie_of_the_Unicorn)

set(CMAKE_CXX_STANDARD 20)

find_library(COREMIDI CoreMidi "/")
find_library(COREFOUNDATION CoreFoundation "/")
find_package(CURL REQUIRED)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(RAPIDJSON_BUILD_TESTS off)
set(RAPIDJSON_BUILD_EXAMPLES off)
set(RAPIDJSON_BUILD_DOC off)
set(RTMIDI_BUILD_TESTING off)
set(RTMIDI_BUILD_STATIC_LIBS on)
set(RAPIDJSON_ENABLE_INSTRUMENTATION_OPT off)
add_subdirectory(rapidjson)

set(RTMIDI_API_CORE ON)
add_subdirectory(rtmidi)

add_subdirectory(googletest)

file(GLOB_RECURSE sources src/*.cpp src/*.h)
file(GLOB_RECURSE test_sources src/*.cpp src/*.h)
list(FILTER test_sources EXCLUDE REGEX ".*main\\.cpp$")

file(GLOB_RECURSE unit_tests test/unit/*.cpp test/unit/*.h test/fakes/*.h)
file(GLOB_RECURSE integration_tests test/integration/*.cpp test/integration/*.h test/fakes/*.h)

add_executable(Mackie_of_the_Unicorn ${sources})

add_dependencies(Mackie_of_the_Unicorn rtmidi)

target_include_directories(Mackie_of_the_Unicorn PUBLIC rapidjson/include rtmidi ${CURL_INCLUDE_DIR})

target_link_libraries(Mackie_of_the_Unicorn ${CMAKE_BINARY_DIR}/rtmidi/librtmidi.a ${CURL_LIBRARIES} "-framework CoreFoundation -framework CoreMIDI -framework CoreAudio")

enable_testing()
add_executable(Unit_Tests ${test_sources} ${unit_tests})
target_link_libraries(Unit_Tests gtest_main gmock)

add_executable(Integration_Tests ${test_sources} ${integration_tests})
target_link_libraries(Integration_Tests gtest_main gmock)

configure_file(${CMAKE_SOURCE_DIR}/src/git_version.h.in ${CMAKE_SOURCE_DIR}/src/git_version.h @ONLY)

option(BUILD_DOC "Build documentation" ON)

if (BUILD_DOC)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        # set input and output files
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

        # request to configure the file
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        message("Doxygen build started")

        # note the option ALL which allows to build the docs together with the application
        add_custom_target( doc ALL
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                COMMENT "Generating API documentation with Doxygen"
                VERBATIM )
    else (DOXYGEN_FOUND)
        message("Doxygen need to be installed to generate the doxygen documentation")
    endif (DOXYGEN_FOUND)
endif()