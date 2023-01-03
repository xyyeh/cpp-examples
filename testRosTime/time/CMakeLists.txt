project(time)

add_library(${PROJECT_NAME} STATIC
    # include/ros/impl/duration.hpp
    # include/ros/impl/time.hpp

    # include/ros/duration.hpp
    # include/ros/time.hpp
    # include/ros/rate.hpp

    src/duration.cpp
    src/rate.cpp
    src/time.cpp
    
    src/timer.cpp
    src/wall_timer.cpp
    src/steady_timer.cpp
    
    src/timer_handle.cpp 
    src/callback_queue.cpp 
)

target_include_directories(${PROJECT_NAME}
  # PRIVATE src
  PUBLIC include
)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)

find_package(Boost REQUIRED COMPONENTS system thread timer chrono) 
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} 
  PRIVATE 
    rt 
  PUBLIC
    Threads::Threads 
    Boost::system 
    Boost::thread 
    Boost::timer
    Boost::chrono
)