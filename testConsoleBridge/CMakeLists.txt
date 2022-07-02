cmake_minimum_required(VERSION 3.6.0)
project(testConsoleBridge)

add_executable(${PROJECT_NAME} main.cpp)

find_package(console_bridge REQUIRED)
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        console_bridge::console_bridge
)