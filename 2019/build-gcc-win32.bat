@echo off

REM Output path (relative to build bat file)
SET OutputPath=.\build

REM Compiler flags
SET OptimizeFlags="-O2"
REM SET DebugFlags="-g"
SET CommonCompilerFlags=-std=c99 -Wall -x c %OptimizeFlags% %DebugFlags%

REM Create output path if doesn't exists
IF NOT EXIST %OutputPath% MKDIR %OutputPath%
PUSHD %OutputPath%

REM Empty the build folder
DEL /Q *

REM Compile the tests
gcc %CommonCompilerFlags% ..\1.c -o 1.exe
gcc %CommonCompilerFlags% ..\2.c -o 2.exe
gcc %CommonCompilerFlags% ..\3.c -o 3.exe
gcc %CommonCompilerFlags% ..\4.c -o 4.exe
gcc %CommonCompilerFlags% ..\5.c -o 5.exe
gcc %CommonCompilerFlags% ..\6.c -o 6.exe
gcc %CommonCompilerFlags% ..\7.c -o 7.exe

POPD
