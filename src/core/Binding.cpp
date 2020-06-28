#include "newbrush/core/Binding.h"
#include "newbrush/core/DataContext.h"

using namespace nb;

Binding::Binding()
	: Binding(nullptr, "", BindingModeE::OneWayToTarget)
{
}

Binding::Binding(const std::string & path)
	: Binding(nullptr, path, BindingModeE::OneWayToTarget)
{
}

Binding::Binding(DataContextPtr source, const std::string & path, BindingModeE mode)
	: m_path(path)
	, m_mode(mode)
{
	setSource(source);
}

void Binding::setMode(BindingModeE mode) &
{
	m_mode = mode;
}

BindingModeE Binding::mode() const
{
	return m_mode;
}

void Binding::setSource(DataContextPtr source) &
{
	m_source = source;
	if (m_source)
	{
		m_source->ValueChanged += [&](const DataContext::ValueChangedArgs & args) {
			if (args.path == path())
				this->BindDataChanged.invoke({ args.value });
		};
	}
}

DataContextPtr Binding::source() const
{
	return m_source;
}

void Binding::setPath(const std::string & path) &
{
	m_path = path;
}

std::string Binding::path() const
{
	return m_path;
}
