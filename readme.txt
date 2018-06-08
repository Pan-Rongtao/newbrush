目录结构

NewBrush
|
|-------Bin		多平台输出目录
|	|
|	|
|	|		     -----release
|	|-------win32-------|
|	|		     -----debug
|	|
|	|		     -----release	
|	|-------Linux-x11---|
|	|		     -----debug
|	|
|	|		     -----release	
|	 -------Linux-arm---|
|			     -----debug
|
|-------Build		多平台工程编译目录
|	|
|	|		     -----Core
|	|-------Win32-------|-----System
|	|		    |-----GlesSvr
|	|		     -----Gui
|	|
|	|		     -----Core
|	|-------Linux-x11---|-----System
|	|		    |-----GlesSvr
|	|		     -----Gui
|	|
|	|		     -----Core
|	 -------Linux-arm---|-----System
|			    |-----GlesSvr
|			     -----Gui
|	
|-------Examples	示例代码工程
|	|
|	|
|	|-------build-x11		各示例工程编译目录
|	|-------build-arm
|	|
|	|-------FscTest
|	|-------NewBrush Test
|	 -------TestApp
|
|
|-------Extern		外部引用
|	|
|	|-------Include	各模块头文件
|	|	|
|	|	|-------gl		opengl、gles、egl等相关
|	|	 -------freetype	字体相关
|	|	
|	|-------Lib	外部库
|
|
|-------Include		各工程头文件目录（输入和输出）
|	|
|	|-----Core
|	|-----System
|	|-----GlesSvr
|	 -----Gui
|	
|
|-------Resource	资源文件
|
|
|
|
|-------Source		各工程源码文件目录
|	|
|	|-----Core
|	|-----System
|	|-----GlesSvr
|	 -----Gui
|	
|
|
|-------Tool		辅助工具，一般为SDK发布工具等
|
|
|
 -------Makefile	linux-x11、linux-arm下使用的全局makefile