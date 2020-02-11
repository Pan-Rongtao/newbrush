#include "Binding.h"

using namespace nb::gui;

Binding::Binding()
	: Binding(nullptr, "", ModeE::OneWayToTarget)
{
}

Binding::Binding(const std::string & path)
	: Binding(nullptr, path, ModeE::OneWayToTarget)
{
}

Binding::Binding(DataContextPtr source, const std::string & path, ModeE mode)
	: m_source(source)
	, m_path(path)
	, m_mode(mode)
{
}

void Binding::setMode(ModeE mode)
{
	m_mode = mode;
}

Binding::ModeE Binding::mode() const
{
	return m_mode;
}

void Binding::setSource(DataContextPtr source)
{
	m_source = source;
}

DataContextPtr Binding::source() const
{
	return m_source;
}

void Binding::setPath(const std::string & path)
{
	m_path = path;
}

std::string Binding::path() const
{
	return m_path;
}
