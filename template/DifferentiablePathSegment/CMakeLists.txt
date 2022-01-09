cmake_minimum_required(VERSION 3.1.3)
project(DifferentiablePathSegment)

add_library(${PROJECT_NAME} STATIC
    inc/DifferentiablePathSegment/DifferentiablePathSegment.hpp
    src/DifferentiablePathSegment.cpp
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