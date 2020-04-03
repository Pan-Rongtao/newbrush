/*******************************************************
**	TransformCollection
**
*表示可按照索引单独访问的Transform 对象的集合。
**
********************************************************/

#pragma once
#include "newbrush/media/Transform.h"

namespace nb {

	class NB_API TransformCollection : public Transform
	{
	public:
		TransformCollection();
		TransformCollection(std::vector<std::shared_ptr<Transform>> collection);
		TransformCollection(size_t capacity);

		//获取TransformCollection 中包含的项数
		size_t count();

		//将Transform 添加到 TransformCollection的末尾
		void add(std::shared_ptr<Transform> value);

		//从TransformCollection 中移除所有项。
		void clear();

		//确定TransformCollection是否包含指定的Transform。
		bool contains(std::shared_ptr<Transform> value);

		//确定TransformCollection中指定项的索引。如果找到了该项，则为 value 的索引；否则为 -1。
		int indexOf(std::shared_ptr<Transform> value);

		//将Transform 插入TransformCollection中的指定索引处。
		void insert(size_t index, std::shared_ptr<Transform> value);

		//从TransformCollection中移除指定的Transform的第一个匹配项。
		bool remove(std::shared_ptr<Transform> value);

		//移除指定索引处的Transform。
		void removeAt(size_t index);

		std::shared_ptr<Transform> getItem(size_t i);

	private:
		std::vector<std::shared_ptr<Transform>> m_collection;
	};
}