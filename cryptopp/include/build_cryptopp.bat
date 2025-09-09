@echo off
REM Lightweight build for Crypto++ (only RSA + DSA support)

SET CPP_COMPILER="C:\Qt\Tools\mingw1310_64\bin\g++.exe"
SET AR_TOOL="C:\Qt\Tools\mingw1310_64\bin\ar.exe"
SET CXX_FLAGS=-DCRYPTOPP_DISABLE_ASM -O2 -g -std=c++17
SET INCLUDE_DIR=.

echo Deleting old object files and library...
del *.o > nul 2>&1
del libcryptopp.a > nul 2>&1

echo Compiling required Crypto++ source files...
%CPP_COMPILER% -c %CXX_FLAGS% -I%INCLUDE_DIR% ^
    cryptlib.cpp integer.cpp nbtheory.cpp osrng.cpp files.cpp filters.cpp queue.cpp ^
    hex.cpp rsa.cpp dsa.cpp pubkey.cpp 

IF %ERRORLEVEL% NEQ 0 (
    echo Compilation failed.
    exit /b 1
)

echo Archiving object files into libcryptopp.a...
%AR_TOOL% rcs libcryptopp.a *.o

IF %ERRORLEVEL% NEQ 0 (
    echo Archiving failed.
    exit /b 1
)

echo.
echo ✅ Crypto++ static library (libcryptopp.a) built successfully with RSA + DSA only!
del *.o > nul 2>&1
