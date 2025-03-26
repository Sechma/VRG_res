# VRG_res
VRG interview application project in c++


# build
``mkdir build`` <br>
``cd build `` <br>
``cmake .. -DCMAKE_TOOLCHAIN_FILE=/home/name/vcpkg/scripts/buildsystems/vcpkg.cmake`` <br>
``make`` <br>
`./main` <br>

# clean
<br>
``make clean``

# run
``./vrg_res -s <shooter_x> <shooter_y> <shooter_z> -g <goal_x> <goal_y> <goal_z> -v <speed_of_shot> -w <weight_of_shot> -e <step_size>``
OR
`` ./vrg_res``
<br>
# requirements
- c++23 >=
- CMake 3.22 >=
- vcpkg git clone https://github.com/microsoft vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
- EnTT (https://github.com/skypjack/entt)
- glm (sudo apt install libglm-dev)
- CLI11 (./vcpkg install cli11)