cmake_minimum_required(VERSION 3.10)
project(VRG_RES)

# Use vcpkg toolchain file to find dependencies
set(CMAKE_TOOLCHAIN_FILE /home/marek/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "vcpkg toolchain file")

# Find EnTT
find_package(EnTT CONFIG REQUIRED)

# Add your executable
add_executable(vrg_res main.cc utils.cc)

# Link EnTT to your executable
target_link_libraries(vrg_res PRIVATE EnTT::EnTT)
