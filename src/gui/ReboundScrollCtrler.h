#pragma once
#include "ReboundScroll.h"
#include "GestureAnalyse.h"
#include "MovePositionAnalyse.h"

namespace nb{ namespace gui {

enum EnumWorkMode
{
	WorkMode_Hor = 0x00,
	WorkMode_Vert
};
class ReboundScrollCtrler
{
public:
	ReboundScrollCtrler();
	virtual ~ReboundScrollCtrler();

	// 鼠标压下
	void PointerPressEvent(nb::core::Point pos);

	// 鼠标移动
	void PointerMoveEvent(nb::core::Point pos);

	// 鼠标释放
	void PointerReleaseEvent(nb::core::Point pos);

	// 将第一项的偏移量置为零
	void ZeroItemOffset();

	// 停止滚动
	void StopScroll();

	// 向增量方向滚动
	void ScrollIncrease(int nItems, float fAccel = 1000.0);

	// 向减量方向滚动
	void ScrollDecrease(int nItems, float fAccel = 1000.0);

	// 滚动指定的距离
	void ScrollDistance(float fDistance, float fAccel);

	// 获取鼠标压下点到压下项开始位置的偏离量
	float GetOffsetOfPressPosToPressItemBegin() const;

	// 是否激活了滚动
	bool IsActiveScroll() const;

	// 是否正在滚动
	bool IsScrolling() const;
	void SetGestureLock(int xGestureLock, int yGestureLock);

public:
	nb::core::Property_rw<int>				ItemCount;
	nb::core::Property_rw<int>				FirstItem;
	nb::core::Property_rw<float>			ItemSize;
	nb::core::Property_rw<float>			FirstItemOffset;
	nb::core::Property_rw<float>			PageSize;
	nb::core::Property_rw<float>			Accel;
	nb::core::Property_rw<float>			ReboundAccel;
	nb::core::Property_rw<float>			MaxSpeed;
	nb::core::Property_rw<float>			HoldBackSpeed;
	nb::core::Property_rw<bool>				CycMode;
	nb::core::Property_rw<int>				PressItem;
	nb::core::Property_rw<EnumWorkMode>		WorkMode;
	nb::core::Property_rw<int>				MinScrollItem;
	nb::core::Property_rw<int>				MaxScrollItem;
			
	struct ScrollArgs { int m_nFirstItem; float m_fFirstItemOffset; EnumWorkMode m_nWorkMode; };
	nb::core::Event<ScrollArgs>				ScrollEvent;

	struct ScrollEndArgs {};
	nb::core::Event<ScrollEndArgs>			ScrollEndEvent;

	struct FirstItemChangedArgs { int oldItem; int newItem; };
	nb::core::Event<FirstItemChangedArgs>	FirstItemChangedEvent;

private:
	void ScrollWork(float fSpeed, float fAccel, bool bUseHoldBackSpeed);
	inline void AdjustDragPos(nb::core::Point posOrigin, nb::core::Point &pos) /*const*/;
	inline int GetVisibleItems() /*const*/;
	inline void AdjustFirstItem();
			
	void OnKineticScroll(const ReboundScroll::ScrollArgs &args);
	void OnKineticScrollEnd(const ReboundScroll::ScrollEndArgs &args);

private:
	std::shared_ptr<ReboundScroll>			m_pReboundScroll;
	std::shared_ptr<GestureAnalyse>			m_pGestureAnalyse;	//该对象分析鼠标手势，计算鼠标的滑动速度
	std::shared_ptr<MovePositionAnalyse>	m_pMovePositionAnalyse;

	float m_fOffsetOfPressPosToPressItemBegin;
	bool m_bScrollByIncDec;
	int m_nPressFirstItem;			//鼠标压下时的第一项的序号
	float m_fPressFirstItemOffset;	//鼠标压下是的第一项的偏移量
};

}}