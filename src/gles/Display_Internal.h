#pragma once
#include <EGL/egl.h>

namespace nb
{
	namespace EGL
	{
		class Display_Internal
		{
		public:
			Display_Internal(EGLNativeDisplayType id);

			EGLNativeDisplayType GetId() const;

			EGLDisplay GetHandle() const;

		public:
			static Display_Internal Default();

		private:
			EGLDisplay				m_Handle;
			EGLNativeDisplayType	m_Id;
		};
	}
}