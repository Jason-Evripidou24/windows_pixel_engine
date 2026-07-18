@echo off
setlocal enabledelayedexpansion

REM ================================
REM Compiler setup (MSVC)
REM ================================
call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat"
set "COMPILER=cl"
set "CFLAGS=/nologo /EHsc /std:c++17 /Zi /W4"

REM ================================
REM Directories
REM ================================
set "SRC_DIR=src"
set "BUILD_DIR=build"
set "OBJ_DIR=%BUILD_DIR%\obj"
set "OUT_EXE=%BUILD_DIR%\app.exe"

REM ================================
REM Create build directories
REM ================================
if not exist %BUILD_DIR% mkdir %BUILD_DIR%
if not exist %OBJ_DIR% mkdir %OBJ_DIR%

REM ================================
REM Optional: clean build
REM ================================
if "%1"=="clean" (
    echo Cleaning build directory...
    rmdir /s /q %BUILD_DIR%
    exit /b 0
)

REM ================================
REM Compile all .cpp files
REM ================================
echo Compiling...

for /r "%SRC_DIR%" %%f in (*.cpp) do (
    set "FULL=%%f"

    REM Get path relative to src folder using substring trick
    set "REL=%%f"
    set "REL=!REL:%CD%\src\=!"

    set "OBJ=%OBJ_DIR%\!REL:.cpp=.obj!"

    for %%d in ("!OBJ!") do mkdir "%%~dpd" 2>nul

    echo [C++] %%f
    cl /DUNICODE /D_UNICODE %CFLAGS% /c "%%f" /Fo:"!OBJ!"

    if errorlevel 1 (
        echo Compilation failed!
        exit /b 1
    )
)

REM ================================
REM Link step
REM ================================
echo Linking...

set "OBJS="

for /r %OBJ_DIR% %%f in (*.obj) do (
    set "OBJS=!OBJS! "%%f""
)

%COMPILER% %CFLAGS% !OBJS! /Fe:%OUT_EXE% user32.lib gdi32.lib

if errorlevel 1 (
    echo Link failed!
    exit /b 1
)

echo.
echo Build successful: %OUT_EXE%
endlocal