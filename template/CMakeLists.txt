cmake_minimum_required(VERSION 3.1)
project(TestTemplate)

# Build the source in this folder
# Recurse in the mybin and mylib folder where you will create an executable and library
add_subdirectory(Example)
add_subdirectory(Library)
