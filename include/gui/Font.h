#pragma once
#include "core/Object.h"

namespace nb{ namespace Media{

class FontPrivate;
class NB_EXPORT Font  : public Core::RefObject
{
public:
	Font();
	Font(std::string sFontName, float fontSize);
	~Font();
	void SetFontName(std::string sFontName);
	void SetFontSize(float fontSize);
	FontPrivate * GetPrivate() const;
private:
	FontPrivate * m_private;
};
typedef nbObjectPtrDerive<Font, Core::RefObjectPtr> FontPtr;

}}
