cmake_minimum_required(VERSION 3.18)

project(BoostProcess)

set(CMAKE_CXX_STANDARD 14)

add_executable(
    ${PROJECT_NAME}
    main.cpp
)

find_package(Boost REQUIRED COMPONENTS filesystem)
include_directories(${Boost_INCLUDE_DIRS})

find_package(Threads REQUIRED)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        Boost::boost 
        Threads::Threads 
        ${Boost_LIBRARIES}
)