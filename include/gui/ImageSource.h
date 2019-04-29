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
#include "../core/Property.h"
#include "../media/Bitmap.h"

namespace nb{ namespace gui {

class NB_API ImageSource
{
public:
	ImageSource();
	ImageSource(const std::string &uri);
	ImageSource(const ImageSource &other) = delete;
	void operator = (const ImageSource &other) = delete;

	void load(const std::string &uri);

public:
	nb::core::Property_r<double>		Width;
	nb::core::Property_r<double>		Height;

private:

	std::shared_ptr<nb::media::Bitmap> 		m_bm;
};

}}
