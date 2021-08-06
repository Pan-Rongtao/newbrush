@echo off

SET ANDROID_SDK_PATH=D:\android-sdk-windows
SET ANDROID_NDK_PATH=%ANDROID_SDK_PATH%\ndk\21.0.6113669
SET ANDROID_CMAKE_TOOLCHAIN=%ANDROID_NDK_PATH%\build\cmake\android.toolchain.cmake
SET ANDROID_CMAKE_PATH=%ANDROID_SDK_PATH%\cmake\3.10.2.4988404
SET ANDROID_NINJA=%ANDROID_CMAKE_PATH%\bin\ninja.exe
SET ANDROID_ABI=arm64-v8a
SET ANDROID_API_LEVEL=24
SET TARGET=android
set dist_dir="..\..\dist\%TARGET%"

set build_dir="build\%TARGET%"
if not exist "%build_dir%" md "%build_dir%"
cd "%build_dir%"

cmake.exe ..\.. -GNinja -DTARGET=%TARGET% -DCMAKE_INSTALL_PREFIX=%dist_dir% ^
        -DCMAKE_TOOLCHAIN_FILE=%ANDROID_CMAKE_TOOLCHAIN% ^
        -DANDROID_NDK=%ANDROID_NDK_PATH% ^
        -DCMAKE_MAKE_PROGRAM=%ANDROID_NINJA% ^
		-DANDROID_ABI=%ANDROID_ABI% ^
        -DANDROID_NATIVE_API_LEVEL=%ANDROID_API_LEVEL% ^
        -DCMAKE_BUILD_TYPE=Release ^
        -DANDROID_FORCE_ARM_BUILD=TRUE ^
        -DANDROID_STL=c++_static ^
        -DANDROID_TOOLCHAIN=clang ^
        -DCMAKE_CXX_FLAGS=-Wno-c++11-narrowing ^
        -DCMAKE_CXX_FLAGS_RELEASE="${CMAKE_CXX_FLAGS_RELEASE} -s"
		
%ANDROID_NINJA%
%ANDROID_NINJA% install
cd ..\..
@pause