cmake_minimum_required(VERSION 3.1.3)
project(Library)

add_library(${PROJECT_NAME} STATIC
    inc/Library/Library.hpp
    src/Library.cpp
    )

target_include_directories(${PROJECT_NAME}
    PUBLIC
        inc   
)

find_package(Eigen3 REQUIRED)
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Eigen3::Eigen
)