# use cmake 3 which supports targets
cmake_minimum_required(VERSION 3.1.3)

project(pimpl)


# create executable from source
add_executable(${PROJECT_NAME} main.cpp vizWrapper.cpp)