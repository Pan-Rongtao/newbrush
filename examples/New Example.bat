@echo off

@title New Example Project

@echo ==================Create Example Project For NewBrush ===================
@echo.

set curDir=%cd%

set /p ProjectName=请输入工程名：

::创建目录结构
if exist "%ProjectName%" (
	@echo 工程[%ProjectName%]已经存在
	goto end
) else (
	@echo 创建工程目录结构：[%ProjectName%]
	md "%ProjectName%"
	md "%ProjectName%/build"
	md "%ProjectName%/bin/win32/debug"
	md "%ProjectName%/bin/win32/release"
	md "%ProjectName%/bin/linux-x11/debug"
	md "%ProjectName%/bin/linux-x11/release"
	md "%ProjectName%/bin/linux-arm/debug"
	md "%ProjectName%/bin/linux-arm/release"
	md "%ProjectName%/src"
	md "%ProjectName%/resource"
)

set sdkroot=../../..

::创建sln文件
set ProjectGUID={009CF489-0230-46B8-A036-DF10935C0028}
set sln="%ProjectName%/build/%ProjectName%.sln"
::由于bat只能写入ansi编码文件，只能由变通的方法保证写出的sln文件为utf8格式（sln必须是带BOM的utf8，不然vs2005识别不了）
::readme.txt是utf8格式的，借用此文件来保证sln为utf8格式
@copy readme.txt %sln%
@echo 写入build/%ProjectName%.sln文件
::表示清除readme.txt原内容
@cd.> %sln%
@echo Microsoft Visual Studio Solution File, Format Version 9.00>> %sln%
@echo # Visual Studio 2005>> %sln%
@echo Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "%ProjectName%", "%ProjectName%.vcproj", "%ProjectGUID%">> %sln%
@echo EndProject>> %sln%
@echo Global>> %sln%
@echo 	GlobalSection(SolutionConfigurationPlatforms) = preSolution>> %sln%
@echo 		Debug^|Win32 = Debug^|Win32>> %sln%
@echo 		Release^|Win32 = Release^|Win32>> %sln%
@echo 	EndGlobalSection>> %sln%
@echo 	GlobalSection(ProjectConfigurationPlatforms) = postSolution>> %sln%
@echo 		%ProjectGUID%.Debug^|Win32.ActiveCfg = Debug^|Win32>> %sln%
@echo 		%ProjectGUID%.Debug^|Win32.Build.0 = Debug^|Win32>> %sln%
@echo 		%ProjectGUID%.Release^|Win32.ActiveCfg = Release^|Win32>> %sln%
@echo 		%ProjectGUID%.Release^|Win32.Build.0 = Release^|Win32>> %sln%
@echo 	EndGlobalSection>> %sln%
@echo 	GlobalSection(SolutionProperties) = preSolution>> %sln%
@echo 		HideSolutionNode = FALSE>> %sln%
@echo 	EndGlobalSection>> %sln%
@echo EndGlobal>> %sln%


::创建vcproj文件
set vcproj="%ProjectName%/build/%ProjectName%.vcproj"
set libs="NBCore.lib NBSystem.lib NBMath.lib NBMedia.lib NBGles.lib NBGui.lib NBNetwork.lib"
@echo 写入build/%ProjectName%.vcproj文件
@echo ^<?xml version="1.0" encoding="gb2312"?^>>> %vcproj%
@echo ^<VisualStudioProject>> %vcproj%
@echo 	ProjectType="Visual C++">> %vcproj%
@echo 	Version="8.00">> %vcproj%
@echo 	Name="%ProjectName%">> %vcproj%
@echo 	ProjectGUID="%ProjectGUID%">> %vcproj%
@echo 	RootNamespace="%ProjectName%">> %vcproj%
@echo 	Keyword="Win32Proj">> %vcproj%
@echo 	^>>> %vcproj%
@echo 	^<Platforms^>>> %vcproj%
@echo 		^<Platform>> %vcproj%
@echo 			Name="Win32">> %vcproj%
@echo 		/^>>> %vcproj%
@echo 	^</Platforms^>>> %vcproj%
@echo 	^<ToolFiles^>>> %vcproj%
@echo 	^</ToolFiles^>>> %vcproj%
@echo 	^<Configurations^>>> %vcproj%
@echo 		^<Configuration>> %vcproj%
@echo 			Name="Debug|Win32">> %vcproj%
@echo 			OutputDirectory="..\bin\$(PlatformName)\$(ConfigurationName)">> %vcproj%
@echo 			IntermediateDirectory="$(ConfigurationName)">> %vcproj%
@echo 			ConfigurationType="1">> %vcproj%
@echo 			CharacterSet="1">> %vcproj%
@echo 			^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCPreBuildEventTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCCustomBuildTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCXMLDataGeneratorTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCWebServiceProxyGeneratorTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCMIDLTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCCLCompilerTool">> %vcproj%
@echo 				Optimization="0">> %vcproj%
@echo				AdditionalIncludeDirectories="%sdkroot%/Include">> %vcproj%
@echo 				PreprocessorDefinitions="WIN32;_DEBUG;_CONSOLE">> %vcproj%
@echo 				MinimalRebuild="true">> %vcproj%
@echo 				BasicRuntimeChecks="3">> %vcproj%
@echo 				RuntimeLibrary="3">> %vcproj%
@echo 				UsePrecompiledHeader="0">> %vcproj%
@echo 				WarningLevel="3">> %vcproj%
@echo 				Detect64BitPortabilityProblems="true">> %vcproj%
@echo 				DebugInformationFormat="4">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCManagedResourceCompilerTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCResourceCompilerTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCPreLinkEventTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCLinkerTool">> %vcproj%
@echo				AdditionalDependencies=%libs%>> %vcproj%
@echo				OutputFile="$(OutDir)\$(ProjectName).exe">> %vcproj%
@echo 				LinkIncremental="2">> %vcproj%
@echo				AdditionalLibraryDirectories="%sdkroot%/Bin/$(PlatformName)/$(ConfigurationName)">> %vcproj%
@echo 				GenerateDebugInformation="true">> %vcproj%
@echo 				SubSystem="1">> %vcproj%
@echo 				TargetMachine="1">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool >> %vcproj%
@echo 				Name="VCALinkTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCManifestTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCXDCMakeTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCBscMakeTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCFxCopTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCAppVerifierTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCWebDeploymentTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCPostBuildEventTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 		^</Configuration^>>> %vcproj%
@echo 		^<Configuration>> %vcproj%
@echo 			Name="Release|Win32">> %vcproj%
@echo 			OutputDirectory="..\bin\$(PlatformName)\$(ConfigurationName)">> %vcproj%
@echo 			IntermediateDirectory="$(ConfigurationName)">> %vcproj%
@echo 			ConfigurationType="1">> %vcproj%
@echo 			CharacterSet="1">> %vcproj%
@echo 			WholeProgramOptimization="1">> %vcproj%
@echo 			^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCPreBuildEventTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCCustomBuildTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCXMLDataGeneratorTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCWebServiceProxyGeneratorTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCMIDLTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCCLCompilerTool">> %vcproj%
@echo				AdditionalIncludeDirectories="%sdkroot%/Include">> %vcproj%
@echo 				PreprocessorDefinitions="WIN32;NDEBUG;_CONSOLE">> %vcproj%
@echo 				RuntimeLibrary="2">> %vcproj%
@echo 				UsePrecompiledHeader="0">> %vcproj%
@echo 				WarningLevel="3">> %vcproj%
@echo 				Detect64BitPortabilityProblems="true">> %vcproj%
@echo 				DebugInformationFormat="3">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCManagedResourceCompilerTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCResourceCompilerTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCPreLinkEventTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCLinkerTool">> %vcproj%
@echo				AdditionalDependencies=%libs%>> %vcproj%
@echo				OutputFile="$(OutDir)\$(ProjectName).exe">> %vcproj%
@echo 				LinkIncremental="1">> %vcproj%
@echo				AdditionalLibraryDirectories="%sdkroot%/Bin/$(PlatformName)/$(ConfigurationName)">> %vcproj%
@echo 				GenerateDebugInformation="true">> %vcproj%
@echo 				SubSystem="1">> %vcproj%
@echo 				OptimizeReferences="2">> %vcproj%
@echo 				EnableCOMDATFolding="2">> %vcproj%
@echo 				TargetMachine="1">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCALinkTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCManifestTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCXDCMakeTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCBscMakeTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCFxCopTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCAppVerifierTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCWebDeploymentTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 			^<Tool>> %vcproj%
@echo 				Name="VCPostBuildEventTool">> %vcproj%
@echo 			/^>>> %vcproj%
@echo 		^</Configuration^>>> %vcproj%
@echo 	^</Configurations^>>> %vcproj%
@echo 	^<References^>>> %vcproj%
@echo 	^</References^>>> %vcproj%
@echo 	^<Files^>>> %vcproj%
@echo 		^<Filter>> %vcproj%
@echo 			Name="Source Files">> %vcproj%
@echo 			Filter="cpp;c;cc;cxx;def;odl;idl;hpj;bat;asm;asmx">> %vcproj%
@echo 			UniqueIdentifier="{4FC737F1-C7A5-4376-A066-2A32D752A2FF}">> %vcproj%
@echo 			^>>> %vcproj%
@echo 		^</Filter^>>> %vcproj%
@echo 		^<Filter>> %vcproj%
@echo 			Name="Header Files">> %vcproj%
@echo 			Filter="h;hpp;hxx;hm;inl;inc;xsd">> %vcproj%
@echo 			UniqueIdentifier="{93995380-89BD-4b04-88EB-625FBE52EBFB}">> %vcproj%
@echo 			^>>> %vcproj%
@echo 		^</Filter^>>> %vcproj%
@echo 		^<Filter>> %vcproj%
@echo 			Name="Resource Files">> %vcproj%
@echo 			Filter="rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx;tiff;tif;png;wav">> %vcproj%
@echo 			UniqueIdentifier="{67DA6AB6-F800-4c08-8B7A-83BB121AAD01}">> %vcproj%
@echo 			^>>> %vcproj%
@echo 		^</Filter^>>> %vcproj%
@echo 	^</Files^>>> %vcproj%
@echo 	^<Globals^>>> %vcproj%
@echo 	^</Globals^>>> %vcproj%
@echo ^</VisualStudioProject^>>> %vcproj%

::创建Makefile文件
set mf="%ProjectName%/build/Makefile"
@echo 写入build/Makefile
@echo MODULES = x11 arm>> %mf%
@echo clean_MODULES = $(patsubst %%,clean_%%, $(MODULES))>> %mf%
@echo.>> %mf%
@echo all: $(MODULES)>> %mf%
@echo clean: $(clean_MODULES)>> %mf%
@echo.>> %mf%
@echo $(MODULES):>> %mf%
@echo 	@make -f Makefile.$@>> %mf%
@echo.>> %mf%
@echo $(clean_MODULES):>> %mf%
@echo 	@make -f Makefile.$(subst clean_,,$@) clean>> %mf%

set libs=-lNBCore -lNBSystem -lNBMath -lNBMedia -lNBGui -lNBGles -lNBNetwork
::创建Makefile.x11文件
set mf_x11="%ProjectName%/build/Makefile.x11"
@echo 写入build/Makefile.x11
@echo OUT_NAME = "$(shell pwd | rev | cut -d '/' -f2 | rev)">> %mf_x11%
@echo.>> %mf_x11%
@echo OUT_DIR = ../bin/linux-x11/release>> %mf_x11%
@echo INCLUDES = -I%sdkroot%/Include>> %mf_x11%
@echo LIBPATHS = -L%sdkroot%/Bin/Linux-x11/release>> %mf_x11%
@echo.>> %mf_x11%
@echo SOURCES  = $(wildcard ../src/*.cpp)>> %mf_x11%
@echo LIBS     = %libs%>> %mf_x11%
@echo.>> %mf_x11%
@echo CXXFLAGS = $(INCLUDES)>> %mf_x11%
@echo LDFLAGS = $(LIBPATHS) $(LIBS)>> %mf_x11%
@echo.>> %mf_x11%
@echo all:>> %mf_x11%
@echo 	@g++ $(SOURCES) $(CXXFLAGS) $(LDFLAGS) -o ${OUT_DIR}/${OUT_NAME}>> %mf_x11%
@echo.>> %mf_x11%
@echo clean:>> %mf_x11%
@echo 	rm -rf ${OUT_DIR}/${OUT_NAME}>> %mf_x11%
@echo.>> %mf_x11%

::创建Makefile.arm文件
set mf_arm="%ProjectName%/build/Makefile.arm"
@echo 写入build/Makefile.arm
@echo OUT_NAME = "$(shell pwd | rev | cut -d '/' -f2 | rev)">> %mf_arm%
@echo.>> %mf_arm%
@echo OUT_DIR = ../bin/linux-arm/release>> %mf_arm%
@echo INCLUDES = -I%sdkroot%/Include>> %mf_arm%
@echo LIBPATHS = -L%sdkroot%/Bin/Linux-arm/release>> %mf_arm%
@echo.>> %mf_arm%
@echo SOURCES  = $(wildcard ../src/*.cpp)>> %mf_arm%
@echo LIBS     = %libs%>> %mf_arm%
@echo.>> %mf_arm%
@echo CXXFLAGS += $(INCLUDES)>> %mf_arm%
@echo LDFLAGS += $(LIBPATHS) $(LIBS)>> %mf_arm%
@echo.>> %mf_arm%
@echo all:>> %mf_arm%
@echo ifeq ($(CXX), g++)>> %mf_arm%
@echo 	@echo "make sure cxx as arm-linux-***, do you forget to set cxx as arm type?">> %mf_arm%
@echo else>> %mf_arm%
@echo 	@$(CXX) $(SOURCES) $(CXXFLAGS) $(LDFLAGS) -o ${OUT_DIR}/${OUT_NAME}>> %mf_arm%
@echo endif>> %mf_arm%
@echo.>> %mf_arm%
@echo clean:>> %mf_arm%
@echo 	rm -rf ${OUT_DIR}/${OUT_NAME}>> %mf_arm%
@echo.>> %mf_arm%

::创建../Makefile文件
set mf_root="%ProjectName%/Makefile"
@echo 写入Makefile
@echo MODULES = x11 arm>> %mf_root%
@echo clean_MODULES = $(patsubst %%,clean_%%, $(MODULES))>> %mf_root%
@echo.>> %mf_root%
@echo all: $(MODULES)>> %mf_root%
@echo clean: $(clean_MODULES)>> %mf_root%
@echo.>> %mf_root%
@echo $(MODULES):>> %mf_root%
@echo 	@cd build \>> %mf_root%
@echo 	^&^& make -f Makefile.$@>> %mf_root%
@echo.>> %mf_root%
@echo $(clean_MODULES):>> %mf_root%
@echo 	@cd build \>> %mf_root%
@echo 	^&^& make -f Makefile.$(subst clean_,,$@) clean>> %mf_root%

::复制
@echo 复制run.sh文件
@copy "..\Bin\Linux-arm\debug\run.sh" "%ProjectName%\bin\linux-arm\debug\"
@copy "..\Bin\Linux-arm\release\run.sh" "%ProjectName%\bin\linux-arm\release\"
@copy "..\Bin\Linux-x11\debug\run.sh" "%ProjectName%\bin\linux-x11\debug\"
@copy "..\Bin\Linux-x11\release\run.sh" "%ProjectName%\bin\linux-x11\release\"

echo.

@echo==================================Done====================================

:end
echo.
pause
