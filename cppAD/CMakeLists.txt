# use cmake 3 which supports targets
cmake_minimum_required(VERSION 3.1.3)

project(cpp_ad)

# create executable from source
add_executable(${PROJECT_NAME} main.cpp)

# to find cppad libraries
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

# link the libraries
find_package(Eigen3 REQUIRED)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Eigen3::Eigen
)