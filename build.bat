@echo off

call vcvarsall.bat x64 > nul 2>&1
mkdir build > nul 2>&1
pushd build

cl -Fe: raytracer.exe -nologo -Oi -GR- -EHa- -MT -Gm- -Od -W4 -WX -wd4201 -wd4127 -wd4100 -FC -Z7 -Fm: lox.map ../src/main.cpp /link -opt:ref

popd

echo:
