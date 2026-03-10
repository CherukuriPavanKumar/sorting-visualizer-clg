@echo off
REM Batch file to compile and run Sorting Visualizer on Windows

echo ========================================
echo   Sorting Algorithm Visualizer
echo   Compilation and Execution Script
echo ========================================
echo.

REM Check if GCC is installed
where gcc >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: GCC compiler not found!
    echo Please install MinGW or TDM-GCC to compile this program.
    echo.
    echo Download from:
    echo - MinGW: https://sourceforge.net/projects/mingw/
    echo - TDM-GCC: https://jmeubank.github.io/tdm-gcc/
    pause
    exit /b 1
)

echo [1/2] Compiling sorting_visualizer.c...
gcc -o sorting_visualizer.exe sorting_visualizer.c -Wall -Wextra -std=c99

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: Compilation failed!
    pause
    exit /b 1
)

echo [2/2] Compilation successful!
echo.
echo Starting Sorting Visualizer...
echo.
timeout /t 2 /nobreak >nul

REM Run the program
sorting_visualizer.exe

echo.
echo Program terminated.
pause
