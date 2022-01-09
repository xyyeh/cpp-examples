cmake_minimum_required(VERSION 3.1.3)
project(Example)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
    PRIVATE 
        DifferentiablePathSegment
    )