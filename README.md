# Turing_Machine_Simulator

## Setup

Either add a system variable named `SFML_GCC_2.6.2_DIR` denoting the path to SFML.
Or, in CMakeLists.txt, replace `$ENV{SFML_GCC_2.6.2_DIR}` with the path of SFML in your system (For example "C:/Libraries/SFML-2.6.2-windows-gcc-13.1.0-mingw-64-bit"). The folder should contain `bin`, `include`, `lib`, etc.
```
# replace the path below with the actual path
set(SFML_LOCAL_DIR $ENV{SFML_GCC_2.6.2_DIR})
```

In project directory, run the below commands
```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" "-DCMAKE_TOOLCHAIN_FILE=../gcc-toolchain.cmake" -S .. -B .
cmake --build .
./simulator.exe
```

Or
```bash
mkdir build ; if ($?) { cd build } ; if ($?) { cmake -G "MinGW Makefiles" "-DCMAKE_TOOLCHAIN_FILE=../gcc-toolchain.cmake" -S .. -B . } ; if ($?) { cmake --build . }; if ($?) { ./simulator.exe } ;
```
For subsequent runs
```bash
cmake --build . ; if ($?) { ./simulator.exe };
```