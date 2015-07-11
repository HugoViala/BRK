@echo off

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build
cl -EHsc -I C:\SDL2\include\ ..\src\brk.cpp C:\SDL2\lib\x64\SDL2.lib C:\SDL2\lib\x64\SDL2main.lib C:\SDL2\lib\x64\SDL2test.lib 
popd
