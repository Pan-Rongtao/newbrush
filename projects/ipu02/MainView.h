#pragma once
#include "../Common.h"

using namespace nb;
/*
enum class IPU02Scene
{
	None,					//无
	ManualParking,			//手动泊车
	AutomaticParking,		//智能泊车_自动泊车
	RemoteParking,			//智能泊车_遥控泊车
	SelfSelectionParking,	//智能泊车_自选车位泊车
	TrainedParking_Protocol,//记忆泊车_协议
	TrainedParking_Brief,	//记忆泊车_简介
	TrainedParking_Main,	//记忆泊车_主页
	TrainedParking_New_Ruku,//记忆泊车_新建入库
	TrainedParking_New_Chuku,//记忆泊车_新建出库
	TrainedParking_ParkingTask,//记忆泊车_执行泊车
};
*/
class MainView : public ViewBase
{
public:
	static MainView *get();

	template<class T>
	void switchView();

protected:
	virtual void init() override;

private:
	ref<Node2D> m_current;
};

template<class T>
void MainView::switchView()
{
	static_assert(std::is_base_of<nb::Node2D, T>::value, "[T] must be Node2D type or it's derived type.");

	auto curType = rttr::type::get(m_current);
	if (rttr::type::get<T>() == curType)
		return;

	m_current = createRef<T>();
	m_root->clearChildren();
	m_root->addChild(m_current);
}
