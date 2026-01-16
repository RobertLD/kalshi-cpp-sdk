cmake_minimum_required(VERSION 3.14.0)
project(
    kalshi-cpp-sdk
    VERSION 0.1.0
    LANGUAGES C CXX
    )

# Specify C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set some policies, so warnings don't bitch
cmake_policy(SET CMP0057 NEW)

# Set some sane defaults
if (MSVC)
  add_compile_options(/W4 /permissive-)
else()
  add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wconversion
  )
endif()

### Dependencies
include(FetchContent)

# SSL
find_package(OpenSSL REQUIRED)

# Boost Asio
find_package(Boost CONFIG REQUIRED
    COMPONENTS
        system
        log
    )

# nlohmann json
FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(nlohmann_json)


### Library

# Add library target
add_library(kalshi-cpp-sdk
    src/client.cpp
)

# Include directories
target_include_directories(kalshi-cpp-sdk PUBLIC
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link dependencies
target_link_libraries(kalshi-cpp-sdk PUBLIC
    Boost::system
    OpenSSL::SSL
    OpenSSL::Crypto
    nlohmann_json::nlohmann_json
)


### Tests
add_subdirectory(external/googletest)
enable_testing()

file(GLOB TEST_SOURCES tests/*.cpp)
add_executable(kalshi-cpp-sdk-tests
     ${TEST_SOURCES}
)
target_link_libraries(kalshi-cpp-sdk-tests
    kalshi-cpp-sdk
    gtest_main
)
add_test(NAME kalshi-cpp-sdk-tests COMMAND kalshi-cpp-sdk-tests)