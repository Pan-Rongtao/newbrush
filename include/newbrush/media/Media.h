#pragma once

namespace nb {
	
//描述如何调节内容大小以适应目标空间
enum class StretchE
{
	Origion			= 0,	//保持原内容大小
	Fill			= 1,	//不保持内容纵横比，调节内容大小以完全且刚好填充目标尺寸
	Uniform			= 2,	//保持内容纵横比，同时调节大小以适应目标尺寸
	UniformToFill	= 3,	//保持内容纵横比，同时调节大小以填充目标尺寸
};

//笔帽样式
enum class PenLineCapE
{
	Flat,		//没有笔帽
	Round,		//圆形笔帽
	Square,		//矩形笔帽
	Triangle,	//三角形笔帽
};

//联接样式
enum class PenLineJoinE
{
	Beval,
	Miter,
	Round,
};


}