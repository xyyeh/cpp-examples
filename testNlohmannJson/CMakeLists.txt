# use cmake 3 which supports targets
cmake_minimum_required(VERSION 3.1.3)

project(json_test)
SET(CMAKE_CXX_FLAGS "-O3")

# create executable from source
add_executable(${PROJECT_NAME} 
    main.cpp)

# find all packages
find_package(nlohmann_json REQUIRED)
find_package(Eigen3 REQUIRED)

# link the libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        nlohmann_json
        Eigen3::Eigen
)