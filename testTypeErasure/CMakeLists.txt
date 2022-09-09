# use cmake 3 which supports targets
cmake_minimum_required(VERSION 3.1.3)

project(testTypeErasure)

# create executable from source
add_executable(${PROJECT_NAME} 
    main.cpp)

# find all packages

# link the libraries
target_link_libraries(${PROJECT_NAME}

)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)