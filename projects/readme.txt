每个工程里，都有个文件夹是放置android工程的。
有两种方法可以新建android工程：

一、自己新建工程
	请查看 doc/特效插件开发 for android 文档说明

二、复制工程法
	1、复制一个android工程（例如cx62b/cx62b)
	2、修改文件夹名（比如MyProject)
	3、setting.gradle修改rootProject.name为自己的工程名
	4、app/build.gradle修改applicationId后缀为自己的工程名
	5、app/src/main/AndroidManifest.xml修改android:label为自己的工程名
	6、在AS中选中app/src/main/java/com.example.app，shift+F6->Rename Package->Refactor->Do Refactor
	7、查找其他所有com.example.xxx字符串的地方，修改xxx为自己的工程名