/*******************************************************
**	ScaleTransform
**
**
********************************************************/

#pragma once
#include "newbrush/media/Transform.h"

namespace nb {

	class NB_API ScaleTransform : public Transform
	{
	public:
		ScaleTransform();
		ScaleTransform(float scaleX, float scaleY);
		ScaleTransform(float scaleX, float scaleY, float centerX, float centerY);
		virtual ~ScaleTransform() = default;

		static DependencyProperty CenterXProperty();
		static DependencyProperty CenterYProperty();
		static DependencyProperty ScaleXProperty();
		static DependencyProperty ScaleYProperty();

		virtual glm::mat4x4 Value() override;

	protected:
		virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args) override;

	private:
		float m_scaleX;
		float m_scaleY;
		float m_centerX;
		float m_centerY;
	};
}
