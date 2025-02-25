cmake_minimum_required (VERSION 3.14.5)

project(ecen330)
include_directories(.)
include_directories(include)
include_directories(my_libs)

# add_compile_options(-Wall -Wextra -pedantic)
# add_compile_options(-Wall -Wextra -pedantic -Werror)

set(BOARD 1)

if (BOARD)
    # These are the options used to compile and run on the physical Zybo board    
    # You will need to compile using "cmake -DBOARD=1"
    
    # This sets up options for the ARM compiler
    include(zybo/xil_arm_toolchain/toolchain.cmake)

    # Places to search for .h header files
    include_directories("zybo/xil_arm_toolchain/bsp/ps7_cortexa9_0/include")

    # link_directories instructs the compiler where it should look for libraries.
    link_directories(zybo)
    link_directories(zybo/xil_arm_toolchain)

    # Provide a precompiled, known-good intervalTimer, buttons, switches, queue.
    # Will want to delete this for 330 - only use this for lasertag.
    link_directories(zybo/lasertag_libs)
    
    # Set this variable to the name of libraries that board executables needs to link to
    set(330_LIBS c gcc zybo xil c)

    # Pass the BOARD variable to the compiler, so it can be used in #ifdef statements
    add_compile_definitions(ZYBO_BOARD=1)

    # Set this variable to the path of the xilinx Vitis tool
    set(XIL_VITIS_PATH /opt/Xilinx/Vitis/2019.2)
else()
    # These options are required if you want to use the Zybo board emulator    

    # This sets up options for the compiler
    include (emulator/emu.cmake)

    # Places to search for .h header files
    include_directories(emulator/include)

    # link_directories instructs the compiler where it should look for libraries.
    link_directories(emulator)

    # Set this variable to the name of libraries that the emulator needs to link to
    set(330_LIBS emu Qt5Widgets Qt5Gui Qt5Core pthread)

    # Include this header file with all emulator builds
    add_definitions(-include emulator.h)
endif()

# Subdirectories to look for other CMakeLists.txt files
add_subdirectory(lab1)
add_subdirectory(lasertag)

# The rest of this file is to add custom targets to the Makefile that is generated by CMake.

# make BOOT.bin ELF_PATH=...
# This target is used to create SD card images (ECEN 390 only).
add_custom_target(BOOT.bin)
add_custom_command(TARGET BOOT.bin
    COMMAND if [ -z \${ELF_PATH} ]\; then echo '\\033[0;31mYou need to specify an ELF_PATH.  For example: make BOOT.bin ELF_PATH=lab1/lab1.elf\\033[0m'\;exit 1\; fi
    COMMAND if [ ! -f \${ELF_PATH} ]\; then echo '\\033[0;31mThe file \${ELF_PATH} does not exist.\\033[0m'\;exit 1\; fi
    COMMAND ${XIL_VITIS_PATH}/bin/sdcard_gen --xpfm ../hw/platform/330_platform.xpfm --sys_config 330_platform --bif ../hw/platform/sw/330_platform/boot/330_platform.bif --bitstream ../hw/330_hw_system.bit --elf \${ELF_PATH},ps7_cortexa9_0
)
