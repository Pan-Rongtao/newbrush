#pragma once

#include "core/Object.h"
#include "core/Event.h"

namespace nb { namespace System 
{

class TimerPrivate;
class NB_EXPORT Timer : public nbObject
{
	NB_OBJECT_TYPE_DECLARE();

public:
	Timer(void);
	virtual ~Timer(void);

	void SetInterval(int msec);
	inline int GetInterval() const { return m_interval; }

    void SetSingleShot(bool singleShot);
    inline bool IsSingleShot() const { return m_isSingleShot; }

	void Start(int msec);

    void Start();
    void Stop();

    bool IsActive() const;

	static void DriveRun();

	TimerPrivate * GetPrivate() const {return m_private;}

	class TimeoutParam : public nbEventParamT<Timer>{};
	nbEvent<TimeoutParam> TimeoutEvent;

private:
	int m_interval;
	bool m_isSingleShot;

	TimerPrivate * m_private;
};

typedef nbObjectPtrDerive<Timer, nbObjectPtr> TimerPtr;

}}
