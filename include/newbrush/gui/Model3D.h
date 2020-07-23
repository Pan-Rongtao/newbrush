/*******************************************************
**	Model3D
**
**	3D组件的基类
**
**	派生类有灯光Light，Model3DGroup
**
**
**	可对各模式的参数进行设置和查询
**	RGB模式：R、G、B（整型参数范围为0~255，浮点参数为0.0~1.0）
**  SHV模式：S、H、B（S[0.0,360.0]、H[0.0,1.0]、B[0.0,1.0]
**
**
**		潘荣涛
**
********************************************************/

#pragma once
#include "newbrush/core/DependencyObject.h"
#include "newbrush/core/Point.h"
#include "glm/glm.hpp"

namespace nb {

class NB_API Model3D : public DependencyObject
{
public:
	DependencyPropertyPtr TransformProperty();	//变换的依赖属性
};

using Model3DPtr = std::shared_ptr<Model3D>;
using Model3DCollectionPtr = std::shared_ptr<std::vector<Model3DPtr>>;
class NB_API Model3DGroup : public Model3D
{
public:
	DependencyPropertyPtr ChildrenProperty();	//Model3DPtr对象集合的依赖属性（Model3DCollectionPtr，默认值nullptr）
};


using Vec2CollectionPtr = std::shared_ptr<std::vector<glm::vec2>>;
using Vec3CollectionPtr = std::shared_ptr<std::vector<glm::vec3>>;
using Int16CollectionPtr = std::shared_ptr<std::vector<int16_t>>;
class Material;
using MaterialPtr = std::shared_ptr<Material>;
class NB_API Mesh3D : public Model3D
{
public:
	static DependencyPropertyPtr PositionsProperty();			//顶点集合的依赖属性（Vec3CollectionPtr, 默认值nullptr)
	static DependencyPropertyPtr TextureCoordinatesProperty();	//纹理坐标集合的依赖属性（Vec2CollectionPtr, 默认值nullptr)
	static DependencyPropertyPtr TriangleIndicesProperty();		//顶点序列集合的依赖属性（Int16CollectionPtr, 默认值nullptr)
	static DependencyPropertyPtr NormalsProperty();				//法向量集合的依赖属性（Vec3CollectionPtr, 默认值nullptr)
	static DependencyPropertyPtr MaterialProperty();			//材质的依赖属性（MaterialPtr, 默认值nullptr)
};

class NB_API Light : public Model3D
{

};


}