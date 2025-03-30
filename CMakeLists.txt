cmake_minimum_required(VERSION 3.10)
project(VRG_RES)

set(CMAKE_TOOLCHAIN_FILE "/home/marek/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "vcpkg toolchain file")
find_package(EnTT CONFIG REQUIRED)
find_package(CLI11 CONFIG REQUIRED)
find_package(Catch2 REQUIRED COMPONENTS Catch2)

add_executable(vrg_res 
    main.cc 
    utils.cc 
    simulation.cc
)

target_link_libraries(vrg_res PRIVATE 
    EnTT::EnTT
    CLI11::CLI11
)

add_executable(vrg_tests
    tests.cc
    simulation.cc
    utils.cc
)

target_link_libraries(vrg_tests PRIVATE
    EnTT::EnTT
    Catch2::Catch2WithMain
)

enable_testing()
add_test(NAME vrg_tests COMMAND vrg_tests)