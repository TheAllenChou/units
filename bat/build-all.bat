@echo off
cd ..

"%VSINSTALLDIR%/../Common7/IDE/devenv.com" "sln/units.sln" /build "Debug"
"%VSINSTALLDIR%/../Common7/IDE/devenv.com" "sln/units.sln" /build "Release"
"%VSINSTALLDIR%/../Common7/IDE/devenv.com" "sln/units.sln" /build "Ship"

cd bat
@echo on
