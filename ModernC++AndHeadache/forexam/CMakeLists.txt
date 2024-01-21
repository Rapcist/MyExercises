cmake_minimum_required(VERSION 3.28.1)
project(123456)


set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}


  PRIVATE
    test.cpp
  PRIVATE
    FILE_SET CXX_MODULES
       BASE_DIRS
        "${CMAKE_CURRENT_SOURCE_DIR}"
      FILES
    hash.cppm
)
