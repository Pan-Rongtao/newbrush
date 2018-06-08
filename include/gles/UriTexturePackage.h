#pragma once
#include <map>
#include "system/String.h"
#include "gles/Texture2D.h"

namespace nb{ namespace gl{ namespace Gles{

class NB_EXPORT UriTexturePackage
{
public:
	static UriTexturePackage & Current();

	//获取一个texture
	nb::gl::Gles::Texture2D *GetExistingTexture(const nb::System::String &uri);

	//存储一个纹理
	void StoreTexture(const nb::System::String &uri, nb::gl::Gles::Texture2D *texture);

	//移除一个uri
	void Remove(const nb::System::String &uri);

	//检测包中是否有uri
	bool Check(const nb::System::String &uri) const;

	UriTexturePackage(){}

private:
	UriTexturePackage(const UriTexturePackage &other) {}
	void operator = (const UriTexturePackage &other) {}

	std::map<nb::System::String, nb::gl::Gles::Texture2D *>		m_mapUris;
	static UriTexturePackage										g_sInstance;
};

}}}
