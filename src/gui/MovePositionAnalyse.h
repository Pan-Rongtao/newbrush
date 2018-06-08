#pragma once

#include "core/Object.h"
#include "system/Point.h"

namespace nb
{
	namespace Gui
	{
		class MovePositionAnalyse : public nbObject
		{
			NB_OBJECT_TYPE_DECLARE();
		public:
			MovePositionAnalyse();
			MovePositionAnalyse(float xLock, float yLock);
			virtual ~MovePositionAnalyse();

			void SetLock(float xLock, float yLock);
			void Start(nb::System::Point pos);
			void Move(nb::System::Point pos);
			void Cancel();
			bool IsActive() const;
			nb::System::Point GetStartPos() const;
			nb::System::Point GetActivePos() const;

		private:
			float m_xLock;
			float m_yLock;
			bool m_bActive;
			bool m_bStart;
			nb::System::Point m_ptOrigin;
			nb::System::Point m_ptActive;
		};
		typedef nbObjectPtrDerive<MovePositionAnalyse, nbObjectPtr> MovePositionAnalysePtr;
	}
}
