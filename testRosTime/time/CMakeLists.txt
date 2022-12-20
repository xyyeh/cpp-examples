project(time)

add_library(${PROJECT_NAME} STATIC
    include/ros/impl/duration.hpp
    include/ros/impl/time.hpp

    include/ros/duration.hpp
    include/ros/time.hpp
    include/ros/rate.hpp

    src/duration.cpp
    src/rate.cpp
    src/time.cpp
)

target_include_directories(${PROJECT_NAME}
  PRIVATE src
  PUBLIC include
)

find_package(Boost REQUIRED)
target_link_libraries(${PROJECT_NAME} 
  PRIVATE rt 
  PUBLIC Boost::boost)