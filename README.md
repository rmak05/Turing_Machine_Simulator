# Turing_Machine_Simulator

## Setup

In CMakeLists.txt add the path of SFML in your system
```
# replace the path below with the actual path
set(SFML_LOCAL_DIR "C:/Libraries/SFML-2.6.2-windows-gcc-13.1.0-mingw-64-bit")
```
The folder (in this case `SFML-2.6.2-windows-gcc-13.1.0-mingw-64-bit`) should contain `bin`, `include`, `lib`, etc.

In project directory, run the below commands
```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" "-DCMAKE_TOOLCHAIN_FILE=../gcc-toolchain.cmake" -S .. -B .
cmake --build .
/simulator.exe
```