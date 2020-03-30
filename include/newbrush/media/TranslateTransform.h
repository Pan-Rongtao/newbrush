/*******************************************************
**	TranslateTransform
**
**
********************************************************/

#pragma once
#include "newbrush/media/Transform.h"

namespace nb {

	class NB_API TranslateTransform : public Transform
	{
	public:
		TranslateTransform();
		TranslateTransform(float offsetX, float offsetY);
		virtual ~TranslateTransform() = default;

		static DependencyProperty XProperty();
		static DependencyProperty YProperty();

		virtual glm::mat4x4 Value() override;

	protected:
		virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args) override;

	private:
		float m_X;
		float m_Y;
	};
}
