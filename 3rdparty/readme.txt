***为了全平台编译通过，设计到的修改点都应该执行***
***如果需要使库的大小较小，应使用-DCMAKE_CXX_FLAGS=-Wno-c++11-narrowing -DCMAKE_CXX_FLAGS_RELEASE="${CMAKE_CXX_FLAGS_RELEASE} -s"参数***

1、assimp
	-git clone https://github.com/assimp/assimp.git
	-git checkout v5.0.1
	（不要编译Tests，cmake命令使用-DASSIMP_BUILD_TESTS=OFF禁用）
	-for QNX, add on line 49 in code/CMakeLists.txt:add_definitions(-std=gnu++11);
	-for QNX, change 'ASSIMP_BUILD_ASSIMP_TOOLS=OFF' on line 87
	-for QNX, copy qnx.cmake to root dir
	-windows下使用build_msvc14.bat编译win32版本
	-windows下使用build_android.bat编译android版本
	-Linux下使用build_linux64.sh编译linux64版本
	-QNX: cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../dist -DQNX_ARCH=aarch64 -DCMAKE_TOOLCHAIN_FILE=../qnx.cmake -DASSIMP_BUILD_TESTS=OFF
	
2、GLFW
	-git clone https://github.com/glfw/glfw.git
	-git checkout 3.3.2
	-windows下使用build_msvc14.bat编译win32版本
	-Linux下使用build_linux64.sh编译linux64版本
		-可能需要安装libxrandr，sudo apt-get install libxrandr-dev
		-可能需要安装libxinerama，sudo apt-get install libxinerama-dev
		-可能需要安装libxcursor，sudo apt-get install libxcursor-dev
		-可能需要安装libxi，sudo apt-get install libxi-dev

3、rttr
	-git clone https://github.com/rttrorg/rttr.git
		-修改CMakeLists.txt，第77行添加add_definitions(-std=c++11)
		-修改src/unit_tests/CMakeLists.txt，屏蔽run_tests相关内容，大概两条
		-修改src/unit_tests/variant/variant_assign_test.cpp，屏蔽a = a;两条代码
		-修改src/examples/CMakeLists.txt 第37行修改为if (MAX_CXX_STANDARD GREATER 11)
	-windows下使用build_msvc14.bat编译win32版本
	-windows下使用build_android.bat编译android版本
	-Linux下使用build_linux64.sh编译linux64版本

4、spdlog（仅头文件）
	-git clone https://github.com/gabime/spdlog.git
	-git checkout v1.8.1

5、catch2（仅头文件）
	-git clone https://github.com/catchorg/Catch2.git
	-git checkout v2.13.2
	
6、stb_*（仅头文件）
	-https://github.com/nothings/stb
	
7、Glad（仅头文件加源码两个文件）
	-https://glad.dav1d.de/生成包glad.zip

注：所有仓库都在外部进行clone和编译，然后移动到newbrush的仓库中
