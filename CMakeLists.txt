cmake_minimum_required(VERSION 3.10)

project(HelloWorld)

find_package(fmt CONFIG REQUIRED)
find_package(unofficial-mysql-connector-cpp CONFIG REQUIRED)

add_executable(HelloWorld main.cpp)

target_link_libraries(HelloWorld PRIVATE fmt::fmt unofficial::mysql-connector-cpp::connector)