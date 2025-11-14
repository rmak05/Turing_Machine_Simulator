cmake_minimum_required(VERSION 4.1.2)

project(TM_SIMULATOR)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# replace the path below with the actual path
set(SFML_LOCAL_DIR $ENV{SFML_GCC_2.6.2_DIR})

set(SFML_DIR "${SFML_LOCAL_DIR}/lib/cmake/SFML")
find_package(SFML 2.6.2 COMPONENTS graphics window system audio network REQUIRED)

include_directories(include)

set(EXECUTABLE_NAME simulator)
add_executable(${EXECUTABLE_NAME}
    src/main.cpp
    src/turing_machine.cpp
    src/simulator.cpp
    src/tape_box.cpp
)

target_link_libraries(${EXECUTABLE_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
    sfml-network
)

set(SFML_BIN_DIR "${SFML_LOCAL_DIR}/bin")
if(NOT SFML_DLLS_COPIED)
    message(STATUS "Copying SFML dlls")

    file(GLOB SFML_DLLS "${SFML_BIN_DIR}/*.dll")

    if(SFML_DLLS)
        file(COPY ${SFML_DLLS} DESTINATION "${CMAKE_BINARY_DIR}/")
        set(SFML_DLLS_COPIED TRUE CACHE BOOL "Flag to determine if SFML dlls have been copied")

        message(STATUS "Copying SFML dlls - done")
    else()
        message(WARNING "No SFML dlls found in ${SFML_BIN_DIR}")
    endif()
endif()