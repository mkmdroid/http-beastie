cmake_minimum_required(VERSION 3.10)
project(http-beastie LANGUAGES CXX)

find_package(Boost REQUIRED COMPONENTS system)

add_executable(http-beastie
    src/main.cpp
    src/utils.cpp
)

target_include_directories(http-beastie PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(http-beastie PRIVATE
    Boost::system
)
