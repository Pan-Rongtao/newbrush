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
	void Start(nb::core::Point pos);
	void Move(nb::core::Point pos);
	void Cancel();
	bool IsActive() const;
	nb::core::Point GetStartPos() const;
	nb::core::Point GetActivePos() const;

private:
	float m_xLock;
	float m_yLock;
	bool m_bActive;
	bool m_bStart;
	nb::core::Point m_ptOrigin;
	nb::core::Point m_ptActive;
};

}}
