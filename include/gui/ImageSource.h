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
#include "system/String.h"
#include "media/Bitmap.h"
#include "core/Object.h"
#include "gles/Texture2D.h"

namespace nb{ namespace Media{

class NB_EXPORT ImageSource : public nbObject
{
	NB_OBJECT_TYPE_DECLARE();

public:
	//设置uri源
	//异常：path不存在
	void SetUri(const nb::System::String &path);

	//获取uri源
	const nb::System::String GetUri() const;

	//获取像素宽
	int GetPixelWidth() const;

	//获取像素高
	int GetPixcelHeight() const;

	//
	nb::gl::Gles::Texture2D *GetTexture() const;

public:
	//构建一个ImageSource，它的源为NULL
	ImageSource();

	//构建一个ImageSource，它的源为path
	ImageSource(const nb::System::String &path);

private:
	ImageSource(const ImageSource &other);
	void operator = (const ImageSource &other);

	
	nb::gl::Gles::Texture2D		*m_Texture;
};
typedef nbObjectPtrDerive<ImageSource, nbObjectPtr>	ImageSourcePtr;

}}
