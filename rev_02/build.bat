@echo off
setlocal EnableDelayedExpansion

REM ============================================================
REM Setup MSVC environment
REM ============================================================
call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat"

REM ============================================================
REM Output directories
REM ============================================================
set BUILD_DIR=build
set OBJ_DIR=%BUILD_DIR%\obj
set OUT=%BUILD_DIR%\engine.exe

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
if not exist "%OBJ_DIR%" mkdir "%OBJ_DIR%"

REM ============================================================
REM Compiler flags
REM ============================================================
set FLAGS=/std:c++17 /EHsc /Od /W3 /DUNICODE /D_UNICODE /nologo /FS

set OBJS=

echo ============================
echo Compiling...
echo ============================

REM ============================================================
REM Compile each .cpp individually
REM ============================================================
for /r src %%f in (*.cpp) do (

    set "FILE=%%f"

    REM Strip project root (robust method)
    set "REL=%%f"
    set "REL=!REL:%CD%\=!"

    REM Convert to obj path
    set "OBJ_PATH=%OBJ_DIR%\!REL:.cpp=.obj!"

    REM Extract directory from OBJ_PATH
    for %%i in ("!OBJ_PATH!") do set "OBJ_DIR_PATH=%%~dpi"

    if not exist "!OBJ_DIR_PATH!" mkdir "!OBJ_DIR_PATH!"

    echo Compiling %%f

    cl /c "%%f" %FLAGS% /Fo"!OBJ_PATH!"

    if errorlevel 1 (
        echo.
        echo BUILD FAILED
        exit /b 1
    )

    set OBJS=!OBJS! "!OBJ_PATH!"
)

echo.
echo Linking...

cl !OBJS! /link user32.lib gdi32.lib /OUT:%OUT%

if errorlevel 1 (
    echo.
    echo LINK FAILED
    exit /b 1
)

echo.
echo BUILD SUCCESS
echo Running...
echo.

%OUT%

endlocal