@echo off

set cwd=%cd%
set src_dir=%cwd%\src
set tests_dir=%cwd%\tests
set lib_dir=%cwd%\lib
set include_dir=%cwd%\include

call vcvarsall.bat x64 > nul 2>&1
mkdir .\build\batch\debug > nul 2>&1
pushd .\build\batch\debug 

set src_files=%src_dir%\main.cpp %src_dir%\point_vector.cpp %src_dir%\pixel.cpp %src_dir%\canvas.cpp %src_dir%\matrix.cpp %src_dir%\file_io.cpp %src_dir%\str.cpp %src_dir%\arr.cpp %src_dir%\test_suite.cpp %src_dir%\utils.cpp
set test_files=%tests_dir%\tests.cpp
set ignore_warnings=-wd4201 -wd4127 -wd4100 -wd4514 -wd4668 -wd5045
set exe_name=raytracer.exe

cl -Fe: %exe_name% -nologo -Oi -GR- -EHsc -MT -MP -Gm- -Od -W0 -WX %ignore_warnings% -FC -Z7 -Fm: lox.map -I%cwd% -Isrc -I%include_dir% %src_files% %test_files% %libs% /link -opt:ref

popd

echo:
