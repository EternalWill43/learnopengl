@echo off
REM Create the build directory if it does not exist
if not exist build (
    mkdir build
)

setlocal enabledelayedexpansion

for %%V in (2022 2019 2017) do (
    if exist "C:\Program Files (x86)\Microsoft Visual Studio\%%V\Community\VC\Auxiliary\Build\vcvars64.bat" (
        set "VCVARS_PATH=C:\Program Files (x86)\Microsoft Visual Studio\%%V\Community\VC\Auxiliary\Build\vcvars64.bat"
        goto :found_vcvars
    )
    if exist "C:\Program Files\Microsoft Visual Studio\%%V\Community\VC\Auxiliary\Build\vcvars64.bat" (
        set "VCVARS_PATH=C:\Program Files\Microsoft Visual Studio\%%V\Community\VC\Auxiliary\Build\vcvars64.bat"
        goto :found_vcvars
    )
)

:found_vcvars
call "%VCVARS_PATH%"

if not "%1"=="--release" (
cl /Zi /EHsc /MD ./src/main.cpp ./src/stb.cpp /I"./includes" /link /LIBPATH:"./libs" opengl32.lib Winmm.lib user32.lib gdi32.lib kernel32.lib shell32.lib glfw3.lib /out:build\main.exe
) else (
cl /DRELEASE /Zi /EHsc /MD ./src/main.cpp ./src/stb.cpp /I"./includes" /link /LIBPATH:"./libs" opengl32.lib Winmm.lib user32.lib gdi32.lib kernel32.lib shell32.lib glfw3.lib /out:build\main.exe
)

if errorlevel 1 (
    echo Compilation failed
    exit /b %errorlevel%
) else (
    echo Compilation succeeded
    exit /b 0
)
