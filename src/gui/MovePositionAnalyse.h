#pragma once
#include "core/Point.h"

namespace nb{ namespace gui {

class MovePositionAnalyse
{
public:
	MovePositionAnalyse();
	MovePositionAnalyse(float xLock, float yLock);
	virtual ~MovePositionAnalyse();

	void SetLock(float xLock, float yLock);
	void Start(Point pos);
	void Move(Point pos);
	void Cancel();
	bool IsActive() const;
	Point GetStartPos() const;
	Point GetActivePos() const;

private:
	float m_xLock;
	float m_yLock;
	bool m_bActive;
	bool m_bStart;
	Point m_ptOrigin;
	Point m_ptActive;
};

}}
