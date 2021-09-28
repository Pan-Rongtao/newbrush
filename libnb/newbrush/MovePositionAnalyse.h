#pragma once
#include "Object.h"
#include "newbrush/UserControl.h"
namespace nb
{
class CMovePositionAnalyse : public Object
{
public:
	CMovePositionAnalyse(int xLock=5, int yLock=5);
	~CMovePositionAnalyse(void);

	// 开始分析
	void Start(Point pos);

	// 移动
	void Move(Point pos);

	// 是否激活
	bool IsActive() const;

	// 获取分析开始时的位置点
	Point GetStartPos() const;

	// 获取激活时的位置点
	Point GetActivePos() const;

	// 取消分析
	void Cancel();

	void SetLock(int xLock, int yLock);

private:
	bool m_bActive;
	Point m_ptOrigin;
	Point m_ptActive;
	int m_xLock;
	int m_yLock;

	bool m_bStart;
};
}