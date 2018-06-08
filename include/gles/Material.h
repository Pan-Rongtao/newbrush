/*******************************************************
**	Material
**
**	材质
**	
**	材质是物体对光的交互（反射、折射等）性质的描述，
**	它最终被表达为颜色，其中也包含纹理这部分数据，以及对
**		光照影响的反映产生的最终效果
**		
**		潘荣涛
**	
********************************************************/
#pragma once
#include "system/Global.h"

namespace nb{ namespace gl{ namespace Gles{

class Program;
class Texture;
class MaterialEventListener;
class NB_EXPORT Material
{
public:
	//设置program
	void SetProgram(Program *program);

	//获取program
	Program *GetProgram() const;

	//设置纹理
	void SetTexture(Texture *texture);

	//获取纹理
	Texture *GetTexture() const;

	//判断是否与材质material相同
	bool Equal(Material *material) const;

	//
	void SetListener(MaterialEventListener *listener);

public:
	//构建一个材质，它的Program为空，纹理为空
	Material();

	//构建一个材质，它的Program为program，它的纹理为空
	Material(Program *program);

	//构建一个材质，它的Program为program，它的纹理texture
	Material(Program *program, Texture *texture);

private:
	Program					*m_Program;
	Texture					*m_Texture;
	MaterialEventListener	*m_Listener;
};

class NB_EXPORT MaterialEventListener
{
public:
	virtual void On_Texture_Changed() {}
};

}}}
