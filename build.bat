@echo off

call vcvarsall.bat x64 > nul 2>&1
mkdir build > nul 2>&1
pushd build

set files=../src/main.cpp ../src/point_vector.cpp ../src/color.cpp ../src/test_suite.cpp
set libs=../lib/raylib.lib user32.lib gdi32.lib msvcrt.lib shell32.lib winmm.lib
set ignore_warnings=-wd4201 -wd4127 -wd4100
set exe_name=raytracer.exe

cl -Fe: %exe_name% -nologo -Oi -GR- -EHa- -MT -Gm- -Od -W4 -WX %ignore_warnings% -FC -Z7 -Fm: lox.map -I.. -Isrc -I../include %files% %libs% /link -opt:ref /NODEFAULTLIB:libcmt

popd

echo:
