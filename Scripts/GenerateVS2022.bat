@echo off
pushd %~dp0\..\
call vendor\premake-5.0.0-beta2-windows\premake5.exe vs2022
popd
PAUSE