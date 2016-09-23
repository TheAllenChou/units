@echo off
cd ..

"%VSINSTALLDIR%/../Common7/IDE/devenv.com" "sln/units.sln" /rebuild "Ship"

cd bat
@echo on
