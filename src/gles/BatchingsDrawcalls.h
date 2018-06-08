#pragma once
#include <vector>

namespace nb{namespace gl{ namespace Gles{

class RenderObject;
class Batching;
class BatchingsDrawcalls
{
public:
	BatchingsDrawcalls();
	~BatchingsDrawcalls();

	//接管一个渲染物，内部会自动进行bathing的策略
	void Charge(RenderObject *renderObject);

	//放逐一个渲染物
	void Eject(RenderObject *renderObject);

	//查询一个渲染物
	RenderObject *Find(RenderObject *renderObject) const;

	//更新一个渲染物的模型数据，如果无此渲染物，将不做任何动作
	void UpdateModel(RenderObject *renderObject);

	//更新一个渲染物的材质，如果无此渲染物，将不做任何动作
	void UpdateMaterial(RenderObject *renderObject);
	
	//获取batching数量
	int GetBatchingCount() const;

	//获取渲染物个数
	int GetRenderObjectCount() const;

	//执行所有batching的绘制
	void DoBatchingsDrawcalls();

private:

	std::vector<Batching *>		m_Batchings;
};

}}}
