/*******************************************************
**	ImageSource
**
**		图片源
**	
**	
**		由路径加载的位图源，
**	
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include "newbrush/media/Bitmap.h"

namespace nb{

class NB_API ImageSource
{
public:
	ImageSource();
	ImageSource(const std::string &uri);

	float width() const;
	float height() const;

	const Bitmap &bitmap() const;

private:
	Bitmap	m_bm;
};

}
