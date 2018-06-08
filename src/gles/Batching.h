/******************************************************************************

* Copyright (c) 2017，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-03

* 简要描述: Batching
				
				批处理，用来描述批量处理渲染物渲染动作的数据结构。
				批处理将掌管渲染物的Draw动作，把所有渲染物的数据一次性
				传递给GPU，达到最少DrawCall的目的，从而提高性能

* 修改记录:

*****************************************************************************/
#pragma once
#include <vector>

namespace nb{namespace gl{namespace Gles{

class RenderObject;
class Batching
{
public:
	//构建一个批处理
	Batching();
	~Batching();

	//接管一个渲染物
	void Charge(RenderObject *renderObject);

	//放逐一个渲染物
	void Eject(RenderObject *renderObject);

	//更新一个渲染物的模型数据
	void UpdateModel(RenderObject *renderObject);

	//渲染物的个数
	int GetObjectsCount() const;

	//获取下标为index的渲染物
	const RenderObject *GetRenderObejct(int index) const;

	//查询渲染物，并返回下标
	//如果找不到，返回-1
	int Find(RenderObject *renderObject);

	//绘制
	void Draw() const;

private:
	Batching(const Batching &other);
	void operator = (const Batching &other);

	std::vector<RenderObject *>		m_ChargedRenderObjects;
	std::vector<float>				m_ModelsDatas;
	std::vector<unsigned short>		m_ModelsIndicesSequence;
	int								m_nActualIndicesCount;
};

}}}