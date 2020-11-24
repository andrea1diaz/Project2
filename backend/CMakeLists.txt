cmake_minimum_required(VERSION 3.5)
project(server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(server server.cpp data_processor.cpp porter_stemming.cpp)

find_package(PkgConfig REQUIRED)

pkg_check_modules(SERVED_PKG REQUIRED IMPORTED_TARGET served)

target_link_libraries(server PkgConfig::SERVED_PKG)

find_package(Boost COMPONENTS system filesystem REQUIRED)
target_link_libraries(server ${Boost_FILESYSTEM_LIBRARY})
target_link_libraries(server ${Boost_SYSTEM_LIBRARY})
