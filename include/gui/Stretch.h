#pragma once

namespace nb{ namespace gui{

//描述如何调节内容大小以适应目标空间
enum StretchE
{
	Origion	=			0,		//保持原内容大小
	Fill =				1,		//不保持内容纵横比，调节内容大小以完全且刚好填充目标尺寸
	Uniform =			2,		//保持内容纵横比，同时调节大小以适应目标尺寸
	UniformToFill =		3,		//保持内容纵横比，同时调节大小以填充目标尺寸
};

}}