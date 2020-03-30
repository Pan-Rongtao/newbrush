#pragma once
#include "newbrush/media/TransformCollection.h"

namespace nb {

	class NB_API TransformGroup : public Transform
	{
	public:
		TransformGroup();

		static DependencyProperty ChildrenProperty();

		virtual glm::mat4x4 Value() override;

	protected:
		virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args) override;

	private:
		std::shared_ptr<TransformCollection> m_transformCollection;
	};
}