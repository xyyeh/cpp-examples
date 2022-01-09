# use cmake 3 which supports targets
cmake_minimum_required(VERSION 3.5)

project(ilqr)

# create executable from source
add_executable(${PROJECT_NAME} src/main.cpp)

# # find all packages
# find_package(pinocchio REQUIRED HINTS ${CMAKE_INSTALL_PREFIX})
# if (NOT ${pinocchio_FOUND})
#     message(STATUS "Not found")
# else()
#     message(STATUS "Found pinocchio: ${pinocchio_DIR}")
# endif()
# # link the libraries
# target_link_libraries(${PROJECT_NAME}
#     PRIVATE
#         pinocchio::pinocchio
# )

# set location of include headers
# target_include_directories(${PROJECT_NAME} PRIVATE $<INSTALL_INTERFACE:include>)

find_package(Eigen3 REQUIRED)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Eigen3::Eigen
)