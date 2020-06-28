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
#include "newbrush/core/Def.h"
#include "glm/glm.hpp"

namespace nb{

class Program;
class Texture;
using TexturePtr = std::shared_ptr<Texture>;
class NB_API Material
{
public:
	//构建一个材质，纹理为空
	Material();
	~Material() = default;

	//构建一个材质，它的Program为program，它的纹理texture
	Material(const std::vector<TexturePtr> &textures);

	Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular);

	//纹理
	std::vector<TexturePtr> &textures();
	const std::vector<TexturePtr> &textures() const;

	//颜色
	glm::vec3 &getAmbient();
	const glm::vec3 &getAmbient() const;

	glm::vec3 &getDiffuse();
	const glm::vec3 &getDiffuse() const;

	glm::vec3 &getSpecular();
	const glm::vec3 &getSpecular() const;

private:
	std::vector<TexturePtr>	m_textures;
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
};

}
