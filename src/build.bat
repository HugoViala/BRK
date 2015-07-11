@echo off

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build
cl -EHsc ..\src\brk.cpp
popd
