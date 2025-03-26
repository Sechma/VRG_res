# VRG_res
VRG interview application project in c++


# build
<br>
``sh mkdir build`` <br>
``sh cd build `` <br>
``sh cmake .. -DCMAKE_TOOLCHAIN_FILE=/home/name/vcpkg/scripts/buildsystems/vcpkg.cmake`` <br>
``sh make`` <br>
`./main` <br>

# clean
<br>
``sh make clean``

# run
``sh ./vrg_res -s <shooter_x> <shooter_y> <shooter_z> -g <goal_x> <goal_y> <goal_z> -v <speed_of_shot> -w <weight_of_shot> -e <step_size>``
OR
``sh ./vrg_res
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