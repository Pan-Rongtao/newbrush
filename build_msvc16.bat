@echo off

set msbuild_execute="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\msbuild.exe"
set target=win32
set build_dir="build\%target%"
set dist_dir="..\..\dist\%target%"
set curdir=%~dp0

if not exist "%build_dir%" md "%build_dir%"
cd "%build_dir%"

cmake ../.. -G "Visual Studio 16 2019" -A Win32 -DCMAKE_INSTALL_PREFIX=%dist_dir%
@%msbuild_execute% INSTALL.vcxproj /p:Configuration="debug"
@%msbuild_execute% INSTALL.vcxproj /p:Configuration="release"

cd "%curdir%"
@pause