To run this cmake project,you need config 5 tools into you system path.
1.cmake bin
2.arm-gnu-toolchain-15.2.rel1 bin for gcc g++.
3.clang+llvm-22.1.4 bin for c/c++ lib.
4.gd32-openocd bin for gd32 debug or OpenOCD-20240916 bin for stm32 debug.
5.ninja bin
通过网盘分享的文件：MCU_Cmaketool
链接: https://pan.baidu.com/s/1IBQ8ovTwv4FGWI-syLBHwA?pwd=5qxv 提取码: 5qxv
There is a minor bug: you need to flash the program once in Keil MDK before you can flash it in the CMake project. This issue occurs because DAPLink fails to recognize the ID register; after the initial flash via Keil, all subsequent downloads will work normally.


There is a minor bug has been fixed



launch.json
{
    "version": "0.2.0",
    "configurations": [
        {
            "cwd": "${workspaceRoot}",
            "type": "cortex-debug",
            "request": "launch",
            "name": "dplinkDebug",
            "servertype": "openocd",
            "serverpath": "D:/Cmake_Tool/gd32-openocd/bin/openocd.exe",
            "executable": "./build/DEMO.elf",
            "runToEntryPoint": "main",
            "svdFile": "./GD32H7xx.svd",
            "configFiles": [
                "interface/cmsis-dap.cfg",
                "target/gd32h7xx.cfg"
            ],
            "serverArgs": [
                "-c",
                "gd32h7xx.cpu configure -work-area-phys 0x20000000 -work-area-size 0x10000 -work-area-backup 0"
            ],
            "toolchainPrefix": "arm-none-eabi",

        }
    ]
}

tasks.json

{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "CMake Configure",
            "type": "shell",
            "command": "cmake",
            "args": [
                "-DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE",
                "-GNinja",
                "-Bbuild"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        },
        {
            "label": "CMake Build",
            "type": "shell",
            "command": "cmake",
            "args": [
                "--build",
                "build",
                "--target",
                "all"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        },
        {
            "label": "Flash",
            "type": "shell",
            "command": "D:/Cmake_Tool/gd32-openocd/bin/openocd.exe",
            "args": [
                "-c",
                "set WORKAREASIZE 0x10000",
                "-f",
                "interface/cmsis-dap.cfg",
                "-f",
                "target/gd32h7xx.cfg",
                "-c",
                "gd32h7xx.cpu configure -work-area-phys 0x20000000 -work-area-size 0x10000 -work-area-backup 0",
                "-c",
                "program ./build/DEMO.elf verify reset exit"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }

    ]
}



