cmake_minimum_required(VERSION 3.6.0)
project(testDoxygen)

add_executable(${PROJECT_NAME} 
    main.cpp
    baseClass.cpp)

find_package(Eigen3 REQUIRED)
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Eigen3::Eigen
)