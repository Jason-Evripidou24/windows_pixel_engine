@echo off
setlocal enabledelayedexpansion

REM ============================================================
REM Setup MSVC environment
REM ============================================================
call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat"

REM ============================================================
REM Output
REM ============================================================
set OUT=engine.exe

REM ============================================================
REM Collect all .cpp files recursively
REM ============================================================
set SOURCES=

for /r application %%f in (*.cpp) do (
    set SOURCES=!SOURCES! "%%f"
)

REM ============================================================
REM Flags
REM ============================================================
set FLAGS=/std:c++17 /EHsc /Zi /Od /W3 /DUNICODE /D_UNICODE

REM ============================================================
REM Link libs
REM ============================================================
set LIBS=user32.lib gdi32.lib

REM ============================================================
REM Build
REM ============================================================
echo ============================
echo Building Pixel Engine...
echo ============================

cl !SOURCES! %FLAGS% /link %LIBS% /OUT:%OUT%

if %errorlevel% neq 0 (
    echo.
    echo BUILD FAILED
    exit /b 1
)

echo.
echo BUILD SUCCESS
echo Running...
echo.

%OUT%

endlocal