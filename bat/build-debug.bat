@echo off
cd ..

"%VSINSTALLDIR%/../Common7/IDE/devenv.com" "sln/units.sln" /build "Debug"

cd bat
@echo on
