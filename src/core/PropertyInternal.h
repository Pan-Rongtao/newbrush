#pragma once

#include <typeinfo>
#include <map>
#include <list>
#include <set>

#include "core/DependencyProperty.h"


namespace nb
{
	namespace Core
	{
		class DependencyProperty;

		class DependencyPropertyInternal
		{
		public:
			DependencyPropertyInternal(void);
			virtual ~DependencyPropertyInternal(void);

			DependencyProperty * PrepareProperty(const std::string &key, const std::type_info &type, const std::type_info &propertyType, bool isExternal, bool isImmobile);
			DependencyProperty * PrepareProperty(const char *pkey, const std::type_info &type, const std::type_info &propertyType, bool isExternal, bool isImmobile);

			DependencyProperty * PrepareProperty(int offset, const char *pkey, const std::type_info &type, const std::type_info &propertyType, bool isExternal, bool isImmobile);

			void AppPreparePropertys();

			size_t GetPreparePropertyCount(const std::string & typeName) const;

		private:
		//	static void SetPropertyElementType(nbDependencyProperty *pProperty, nbType *pElementType);

			class TypePropertys
			{
			public:
				struct Info
				{
					std::string m_key;
					std::string m_sElementType;
					DependencyPropertyPtr m_pProperty;
					bool m_isExternal;
					int m_offset;
				};

			public:
				~TypePropertys();
				DependencyProperty * NewProperty(int offset, const char *pkey, const std::type_info &type, bool isExternal, bool isImmobile);
				DependencyProperty * NewProperty(int offset, const std::string &key, const std::type_info &type, bool isExternal, bool isImmobile);

				std::list<Info *> m_lst;
			};

		private:
			void TypePropertys_ApplyPropertys(TypePropertys *pTP, Type *pType);

			std::map<std::string, TypePropertys *> m_mapPrepare;

			friend class DependencyPropertyInternal::TypePropertys;
		};
	}
}
