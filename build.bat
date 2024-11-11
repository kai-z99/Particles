@echo off
g++ -o main.exe src/*.cpp -I"include" -I"libs/raylib/include" "libs/raylib/lib/libraylib.a" -lgdi32 -lwinmm -O3
pause
