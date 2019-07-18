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

public:
	float width() const;
	float heigth() const;

	nb::core::Property_rw<std::shared_ptr<media::Bitmap>> 	Bm;

private:

};

}}
