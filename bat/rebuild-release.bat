@echo off
cd ..

"%VSINSTALLDIR%/../Common7/IDE/devenv.com" "sln/units.sln" /rebuild "Release"

cd bat
@echo on
