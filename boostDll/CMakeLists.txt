cmake_minimum_required(VERSION 3.18)

project(BoostOptions)

set(CMAKE_CXX_STANDARD 14)

add_executable(
    ${PROJECT_NAME}
    main.cpp
)

find_package(Boost 1.71 COMPONENTS filesystem system REQUIRED)
find_package(spdlog 1.5 REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIR})

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
        spdlog::spdlog
        ${Boost_LIBRARIES}
)