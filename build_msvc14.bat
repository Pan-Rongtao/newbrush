@echo off

set msbuild_execute="C:\Program Files (x86)\MSBuild\14.0\Bin\msbuild.exe"
set target=win32
set build_dir="build\%target%"
set dist_dir="..\..\dist\%target%"

if not exist "%build_dir%" md "%build_dir%"
cd "%build_dir%"

cmake ../.. -G "Visual Studio 14 2015" -DCMAKE_INSTALL_PREFIX=%dist_dir%
@%msbuild_execute% INSTALL.vcxproj /p:Configuration="debug"
@%msbuild_execute% INSTALL.vcxproj /p:Configuration="release"

@pause