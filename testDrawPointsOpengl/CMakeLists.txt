cmake_minimum_required(VERSION 3.10)

project(testDrawPointsOpengl)
add_executable(${PROJECT_NAME} main.cpp)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLUT REQUIRED)
find_package(GLU REQUIRED)

add_dependencies(${PROJECT_NAME} OpenGL::OpenGL)
include_directories(${GLUT_INCLUDE_DIRS} )

target_link_libraries(${PROJECT_NAME} OpenGL::OpenGL ${GLU_LIBRARY} ${GLUT_LIBRARY} )