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
#include <vector>
#include "../core/Def.h"
#include "Program.h"
#include "Texture.h"

namespace nb{ namespace gl{

class NB_API Material
{
public:
	//构建一个材质，它的Program为空，纹理为空
	Material();

	//构建一个材质，它的Program为program，它的纹理为空
	Material(std::shared_ptr<Program> program);

	//构建一个材质，它的Program为program，它的纹理texture
	Material(std::shared_ptr<Program> program, const std::vector<std::shared_ptr<Texture>> &textures);

public:
	//设置program
	void setProgram(std::shared_ptr<Program> program);

	//获取program
	std::shared_ptr<Program> program();

	//纹理
	std::vector<std::shared_ptr<Texture>> &textures();
	const std::vector<std::shared_ptr<Texture>> &textures() const;

private:
	std::shared_ptr<Program>				m_program;
	std::vector<std::shared_ptr<Texture>>	m_textures;
};

}}
