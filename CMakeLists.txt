cmake_minimum_required(VERSION 3.10)
project(VRG_RES)

set(CMAKE_TOOLCHAIN_FILE "/home/marek/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "vcpkg toolchain file")

include_directories("/home/marek/vcpkg/installed/x64-linux/include")

add_executable(vrg_res main.cc utils.cc simulation.cc)


find_package(EnTT CONFIG REQUIRED)
find_package(CLI11 CONFIG REQUIRED)

target_link_libraries(vrg_res PRIVATE EnTT::EnTT)

target_link_libraries(vrg_res PRIVATE CLI11::CLI11)
