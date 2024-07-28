@echo off

set cwd=%cd%
set src_dir=%cwd%\src
set tests_dir=%cwd%\tests
set lib_dir=%cwd%\lib
set include_dir=%cwd%\include

call vcvarsall.bat x64 > nul 2>&1
mkdir .\build\batch\debug > nul 2>&1
pushd .\build\batch\debug 

set src_files=%src_dir%\main.cpp %src_dir%\point_vector.cpp %src_dir%\pixel.cpp %src_dir%\canvas.cpp %src_dir%\file_io.cpp %src_dir%\test_suite.cpp
set test_files=%tests_dir%\tests.cpp %tests_dir%\test_point_vector.cpp %tests_dir%\test_color.cpp %tests_dir%\test_canvas.cpp
set libs=%lib_dir%\raylib.lib user32.lib gdi32.lib msvcrt.lib shell32.lib winmm.lib
set ignore_warnings=-wd4201 -wd4127 -wd4100
set exe_name=raytracer.exe

cl -Fe: %exe_name% -nologo -Oi -GR- -EHa- -MT -Gm- -Od -W4 -WX %ignore_warnings% -FC -Z7 -Fm: lox.map -I%cwd% -Isrc -I%include_dir% %src_files% %test_files% %libs% /link -opt:ref /NODEFAULTLIB:libcmt

popd

echo:
