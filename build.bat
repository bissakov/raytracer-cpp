@echo off
setlocal

set cwd=%cd%
set src_dir=%cwd%\src
set geometry_dir=%src_dir%\geometry
set render_dir=%src_dir%\render
set core_dir=%src_dir%\core
set tests_dir=%cwd%\tests
set lib_dir=%cwd%\lib
set include_dir=%cwd%\include

call vcvarsall.bat x64 > nul 2>&1
mkdir .\build\batch\debug > nul 2>&1
pushd .\build\batch\debug 

set entry=%src_dir%\main.cpp
set src_files=%geometry_dir%\point.cpp %geometry_dir%\vector.cpp %render_dir%\color.cpp ^
	%render_dir%\canvas.cpp %geometry_dir%\matrix.cpp %geometry_dir%\ray.cpp ^
	%render_dir%\light.cpp %render_dir%\material.cpp ^
	%core_dir%\file_io.cpp %core_dir%\arr.cpp %core_dir%\test_suite.cpp ^
	%core_dir%\utils.cpp
set test_files=%tests_dir%\tests.cpp

REM set third_party=User32.lib Gdi32.lib Shell32.lib
set includes=-I%cwd% /I"%src_dir%" ^
	-I%include_dir% %entry% %src_files% %test_files%

set warnings=-W4 -WX -wd4201 -wd4127 -wd4100 -wd4514 -wd4668 -wd5045
set exe_name=raytracer.exe

cl -Fe: %exe_name% -std:c++20 -nologo ^
	-Oid -GR- -EHs -MT -MP -Gm- %warnings% -FC -Zi -Fm: lox.map ^
	%includes% %third_party% /link -opt:ref | gnomon

if errorlevel 1 del %exe_name% && echo Build failed...

popd
endlocal
echo:
