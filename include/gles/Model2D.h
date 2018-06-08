/*******************************************************
**	Model2D
**
**	2D模型
**	
**	2D模型描述了一种每个顶点都具有同一z深度的模型
**	即使模型中对每个顶点都设置了不一样的z深度（使用Position3D作为位置数据类型）
**	也会讲每个顶点调整到一样的z深度	
**		
**		潘荣涛
**	
********************************************************/

#pragma once
#include "Model.h"

namespace nb{ namespace gl{ namespace Gles{


class NB_EXPORT Model2D : public Model
{
public:
	//构建一个2D模型，它的深度为0.0
	Model2D(int nVertexCount, nb::System::EnumFlags<Model::VertexAttributesType> flags);

	//构建一个2D模型，它的深度为z
	Model2D(int nVertexCount, nb::System::EnumFlags<Model::VertexAttributesType> flags, float z);

public:
	void SetZ(float z);

	//获取z深度
	float GetZ() const;


};

}}}