@echo off

call vcvarsall.bat x64 > nul 2>&1
mkdir build > nul 2>&1
pushd build

set files=../tests/tests.cpp ../src/point_vector.cpp ../src/pixel.cpp ../src/canvas.cpp ../src/test_suite.cpp
set ignore_warnings=-wd4201 -wd4127 -wd4100
set exe_name=tests.exe

cl -Fe: %exe_name% -nologo -Oi -GR- -EHa- -MT -Gm- -Od -W4 -WX %ignore_warnings% -FC -Z7 -Fm: lox.map /I.. /Isrc /Iinclude %files% /link -opt:ref

popd

echo:
