cmake_minimum_required(VERSION 3.28.1)
project(Ex1 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}

  PRIVATE
    main.cpp
  PRIVATE
    FILE_SET CXX_MODULES
       BASE_DIRS
        "${CMAKE_CURRENT_SOURCE_DIR}"
      FILES
      ex1.cppm
      def.cppm
      ctad.cppm

)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

