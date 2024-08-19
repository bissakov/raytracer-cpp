@echo off
setlocal

set cwd=%cd%
set src_dir=%cwd%\src
set tests_dir=%cwd%\tests
set lib_dir=%cwd%\lib
set include_dir=%cwd%\include

call vcvarsall.bat x64 > nul 2>&1
mkdir .\build\batch\debug > nul 2>&1
pushd .\build\batch\debug 

set entry=%src_dir%\main.cpp
set src_files=%src_dir%\point.cpp %src_dir%\vector.cpp %src_dir%\color.cpp ^
	%src_dir%\canvas.cpp %src_dir%\matrix.cpp %src_dir%\ray.cpp ^
	%src_dir%\light.cpp %src_dir%\material.cpp ^
	%src_dir%\file_io.cpp %src_dir%\arr.cpp %src_dir%\test_suite.cpp ^
	%src_dir%\utils.cpp
set test_files=%tests_dir%\tests.cpp

REM set third_party=User32.lib Gdi32.lib Shell32.lib
set includes=-I%cwd% -Isrc -I%include_dir% %entry% %src_files% %test_files%

set warnings=-W4 -WX -wd4201 -wd4127 -wd4100 -wd4514 -wd4668 -wd5045
set exe_name=raytracer.exe

cl -Fe: %exe_name% -std:c++20 -nologo ^
	-Oid -GR- -EHs -MT -MP -Gm- %warnings% -FC -Zi -Fm: lox.map ^
	%includes% %third_party% /link -opt:ref | gnomon

if errorlevel 1 del %exe_name% && echo Build failed...

popd
endlocal
echo:
