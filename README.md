# VRG_res
VRG interview application project in c++
<br>
Author: Marek Sechra


# build
``mkdir build`` <br>
``cd build `` <br>
``cmake .. -DCMAKE_TOOLCHAIN_FILE=/home/name/vcpkg/scripts/buildsystems/vcpkg.cmake`` <br>
``make`` <br>
`./main` <br>

# clean
``make clean``

# run
``~/build ./vrg_res -s <shooter_x> <shooter_y> <shooter_z> -g <goal_x <goal_y> <goal_z> -v <speed_of_shot> -w <weight_of_shot> -e <step_size>``
OR
`` ./vrg_res``
<br>

# Usage:
``./vrg_res -s "10.0 10.0 1.0" -g "20.0 20.0 1.0" -v 300 -w 0.01 -e 0.00001``
``./vrg_res  # Will prompt for input values``
<br>
# Test
`` vrg_test ``

## requirements
- **Compiler**: C++23 compatible (g++ 11+ or clang 14+)
- **Build System**:
  - CMake 3.22+
  - vcpkg package manager
- **Libraries**:
  - EnTT v3.11+
  - GLM
  - CLI11
  - Catch2 (for tests)

## Physics Model

### The simulation models:
    - Projectile motion with gravity (9.81 m/s²)
    - Used Units:
        - Position: meters (m)
        - Speed: meters/second (m/s)
        - Time: seconds (s)
        - Weight: kilograms (kg)
        - Drag force: Newtons (N) 
        - cceleration: m/s²

### Coordinate System
   - X-axis: Right (+) / Left (-)
   - Y-axis: Forward (+) / Backward (-)
   - Z-axis: Up (+) / Down (-)