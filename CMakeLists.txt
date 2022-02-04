cmake_minimum_required(VERSION 3.21)
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
file(GLOB_RECURSE tests test/*.cpp test/*.h)

add_executable(Mackie_of_the_Unicorn ${sources})

add_dependencies(Mackie_of_the_Unicorn rtmidi)

target_include_directories(Mackie_of_the_Unicorn PUBLIC rapidjson/include rtmidi ${CURL_INCLUDE_DIR})

target_link_libraries(Mackie_of_the_Unicorn ${CMAKE_BINARY_DIR}/rtmidi/librtmidi.a ${CURL_LIBRARIES} "-framework CoreFoundation -framework CoreMIDI -framework CoreAudio")

enable_testing()
add_executable(Mackie_of_the_Unicorn_Tests ${test_sources} ${tests})
target_link_libraries(Mackie_of_the_Unicorn_Tests gtest_main gmock)

include(GoogleTest)
gtest_discover_tests(Mackie_of_the_Unicorn_Tests)
