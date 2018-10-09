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

	void load(const std::string &uri);

public:
	nb::core::Property_r<double>		Width = nb::core::Property_r<double>( property_getter(double) { return m_bm ? m_bm->width() : 0.0; } );
	nb::core::Property_r<double>		Height = nb::core::Property_r<double>( property_getter(double) { return m_bm ? m_bm->width() : 0.0; } );

private:
	ImageSource(const ImageSource &other);
	void operator = (const ImageSource &other);

	std::shared_ptr<nb::media::Bitmap> 		m_bm;
};

}}
