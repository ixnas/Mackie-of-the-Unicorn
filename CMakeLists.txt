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
string(TIMESTAMP YEAR "%Y")
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
    set(OS_FLAGS z "-framework CoreFoundation -framework CoreMIDI -framework CoreAudio")
elseif (MSVC)
    set(OS_FLAGS winmm.lib Ws2_32.lib Wldap32.lib)
else ()
    set(OS_FLAGS "")
endif ()
add_compile_definitions(TARGET_OS_IPHONE=0)
add_compile_definitions(_LIBCPP_DISABLE_AVAILABILITY=1)
set(RAPIDJSON_BUILD_TESTS off)
set(RAPIDJSON_BUILD_EXAMPLES off)
set(RAPIDJSON_BUILD_DOC off)
set(RTMIDI_BUILD_TESTING off)
set(RTMIDI_BUILD_STATIC_LIBS on)
set(RAPIDJSON_ENABLE_INSTRUMENTATION_OPT off)
set(wxBUILD_PRECOMP OFF)
set(wxBUILD_SHARED OFF)
set(CURL_ENABLE_SSL OFF)
set(ENABLE_IPV6 OFF)
set(CURL_DISABLE_LDAP ON)
set(CURL_DISABLE_ALTSVC ON)
set(CURL_DISABLE_HSTS ON)
set(CURL_DISABLE_LDAPS ON)
set(CURL_DISABLE_PROXY ON)
set(CURL_STATICLIB ON)
set(ENABLE_ARES OFF)
set(BUILD_SHARED_LIBS OFF)

# Include dependencies
add_subdirectory(${CMAKE_SOURCE_DIR}/ext/rapidjson)
add_subdirectory(${CMAKE_SOURCE_DIR}/ext/rtmidi EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_SOURCE_DIR}/ext/curl)
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

# Linking libraries
if (MSVC)
    set(RTMIDILIB ${CMAKE_BINARY_DIR}/ext/rtmidi/Release/rtmidi.lib)
    set(CURLLIB ${CMAKE_BINARY_DIR}/ext/curl/lib/Release/libcurl.lib)
else ()
    set(RTMIDILIB ${CMAKE_BINARY_DIR}/ext/rtmidi/librtmidi.a)
    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        set(CURLLIB ${CMAKE_BINARY_DIR}/ext/curl/lib/libcurl.a)
    else()
        set(CURLLIB ${CMAKE_BINARY_DIR}/ext/curl/lib/libcurl-d.a)
    endif()
endif()

# Sources
file(GLOB_RECURSE sources src/*.cpp src/*.h)
list(FILTER sources EXCLUDE REGEX ".*main\\.cpp$")
list(APPEND sources ${MAIN_EXECUTABLE})
if (WIN32)
    list(APPEND sources windows/rc.rc)
endif()

# Sources except main, for tests
file(GLOB_RECURSE test_sources src/*.cpp src/*.h)
list(FILTER test_sources EXCLUDE REGEX ".*main\\.cpp$")

# Test sources
file(GLOB_RECURSE unit_tests test/unit/*.cpp test/unit/*.h test/fakes/*.h)
file(GLOB_RECURSE integration_tests test/integration/*.cpp test/integration/*.h test/fakes/*.h)

# Main executable
if (APPLE)
    set(APP_ICON macos/Resources/Icon.icns)
    set_source_files_properties(${APP_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    add_executable(Mackie_of_the_Unicorn MACOSX_BUNDLE ${APP_ICON} ${sources})
    set_target_properties(Mackie_of_the_Unicorn PROPERTIES
            MACOSX_BUNDLE_BUNDLE_NAME "Mackie of the Unicorn"
            MACOSX_BUNDLE_BUNDLE_ICON_FILE "Icon.icns"
            MACOSX_BUNDLE_BUNDLE_VERSION ${GIT_VERSION}
            MACOSX_BUNDLE_BUNDLE_LONG_VERSION_STRING ${GIT_VERSION}
            MACOSX_BUNDLE_BUNDLE_SHORT_VERSION_STRING ${GIT_VERSION}
            MACOSX_BUNDLE_GUI_IDENTIFIER "nl.sjoerdscheffer"
            MACOSX_BUNDLE_COPYRIGHT "Copyright © ${YEAR} Sjoerd Scheffer"
            )
else ()
    add_executable(Mackie_of_the_Unicorn ${sources})
endif ()

add_dependencies(Mackie_of_the_Unicorn rtmidi ${WX_LIBRARIES} libcurl)
target_include_directories(Mackie_of_the_Unicorn PRIVATE ext/rapidjson/include rtmidi ext/curl/include)
target_link_libraries(Mackie_of_the_Unicorn ${RTMIDILIB} ${CURLLIB} ${WX_LIBRARIES} ${OS_FLAGS})
target_precompile_headers(Mackie_of_the_Unicorn PRIVATE src/precomp.h)
target_compile_definitions(Mackie_of_the_Unicorn PRIVATE CURL_STATICLIB=1)
if (MSVC)
    if (BUILD_GUI)
        set_target_properties(Mackie_of_the_Unicorn PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
    endif()
endif()

# Tests
if (BUILD_TESTS)
    enable_testing()

    # Unit tests
    add_executable(Unit_Tests ${test_sources} ${unit_tests})
    add_dependencies(Unit_Tests rtmidi)
    target_include_directories(Unit_Tests PRIVATE ext/rapidjson/include rtmidi ${CURL_INCLUDE_DIR})
    target_link_libraries(Unit_Tests gtest_main gmock ${RTMIDILIB} ${CURLLIB} ${OS_FLAGS})
    target_precompile_headers(Unit_Tests PRIVATE src/precomp.h)
    target_compile_definitions(Unit_Tests PRIVATE TESTING=1 CURL_STATICLIB=1)

    # Integration tests
    add_executable(Integration_Tests ${test_sources} ${integration_tests})
    add_dependencies(Integration_Tests rtmidi)
    target_include_directories(Integration_Tests PRIVATE ext/rapidjson/include rtmidi ${CURL_INCLUDE_DIR})
    target_link_libraries(Integration_Tests gtest_main gmock ${RTMIDILIB} ${CURLLIB} ${OS_FLAGS})
    target_precompile_headers(Integration_Tests PRIVATE src/precomp.h)
    target_compile_definitions(Integration_Tests PRIVATE TESTING=1 CURL_STATICLIB=1)
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
