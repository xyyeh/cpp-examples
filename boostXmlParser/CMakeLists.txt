# use cmake 3 which supports targets
cmake_minimum_required(VERSION 3.1.3)

project(boost_xml_parser)


# create executable from source
add_executable(${PROJECT_NAME} main.cpp)

# find all packages
find_package(Boost REQUIRED)
if(NOT TARGET Boost::filesystem)
    add_library(Boost::filesystem IMPORTED INTERFACE)
    set_property(TARGET Boost::filesystem PROPERTY
        INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
    set_property(TARGET Boost::filesystem PROPERTY
        INTERFACE_LINK_LIBRARIES ${Boost_LIBRARIES})
endif()

# link the libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Boost::filesystem
)