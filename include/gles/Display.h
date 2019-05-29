/*******************************************************
**	Display
**
**	现实对象类
**		Display是elg抽象的显示设备，所有的gl
**	操作都基于display的初始化
**
**		潘荣涛
**
********************************************************/
#pragma once
#include "../core/Def.h"

namespace nb{ namespace gl{

class NB_API Display
{
public:
	//构建一个ID为id的Display，并进行初始化，如果构建失败，将抛出异常
	Display(long id);

	//默认Display
	static Display defaultx();

	//是否为空
	bool isNull() const;

	//获取id
	long id() const;

	//句柄
	void *handle() const;

private:
	void				*m_handle;
	long				m_id;
};

}}
