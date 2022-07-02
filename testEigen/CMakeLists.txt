cmake_minimum_required(VERSION 3.1.3)
project(testEigen)

add_executable(${PROJECT_NAME} main.cpp)

find_package(Eigen3 REQUIRED)
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Eigen3::Eigen
)