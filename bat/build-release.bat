@echo off
cd ..

"%VSINSTALLDIR%/../Common7/IDE/devenv.com" "sln/units.sln" /build "Release"

cd bat
@echo on
