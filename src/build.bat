@echo off

set CommonCompilerFlags=-MTd -nologo -Gm- -GR- -EHa- -Od -Oi -WX -W4 -wd4201 -wd4100 -wd4189 -wd4505 -FC -Zi
set CommonIncludeFlags=-I C:\SDL2\include\
set CommonLinkerFlag=C:\SDL2\lib\x64\SDL2.lib C:\SDL2\lib\x64\SDL2main.lib C:\SDL2\lib\x64\SDL2test.lib Winmm.lib

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build
cl %CommonCompilerFlags% %CommonIncludeFlags%  ..\src\win32_brk.cpp ..\src\brk.cpp ..\src\vector2.cpp %CommonLinkerFlag%  
popd
