@echo off
REM Create the build directory if it does not exist
if not exist build (
    mkdir build
)

REM Compile the program
cl /Zi /EHsc /MD ./src/main.cpp ./src/stb.cpp /I"./includes" /link /LIBPATH:"./libs" opengl32.lib user32.lib gdi32.lib kernel32.lib shell32.lib glfw3.lib /out:build\main.exe

REM Check for compilation success
if errorlevel 1 (
    echo Compilation failed
    exit /b %errorlevel%
) else (
    echo Compilation succeeded
    exit /b 0
)
