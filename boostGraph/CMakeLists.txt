# use cmake 3 which supports targets
cmake_minimum_required(VERSION 3.1.3)

project(boost_graph)
SET(CMAKE_CXX_FLAGS "-O3")

# create executable from source
add_executable(${PROJECT_NAME} main.cpp DynamicRoadmapBoost.cpp)

# find all packages
find_package(Boost 1.71 COMPONENTS program_options graph REQUIRED)
if(NOT TARGET Boost::graph)
    add_library(Boost::graph IMPORTED INTERFACE)
    set_property(TARGET Boost::graph PROPERTY
        INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
    set_property(TARGET Boost::graph PROPERTY
        INTERFACE_LINK_LIBRARIES ${Boost_LIBRARIES})
endif()

# link the libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Boost::graph
)