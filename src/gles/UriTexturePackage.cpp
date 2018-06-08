#include "gles/UriTexturePackage.h"

using namespace nb::gl::Gles;
UriTexturePackage			UriTexturePackage::g_sInstance;

UriTexturePackage & UriTexturePackage::Current()
{
	return g_sInstance;
}

Texture2D *UriTexturePackage::GetExistingTexture(const nb::System::String &uri)
{
	//路径是否存在
	//if()
	//	return NULL;

	std::map<nb::System::String, Texture2D *>::const_iterator iterFind = m_mapUris.find(uri);
	return iterFind == m_mapUris.end() ? (Texture2D *)NULL : iterFind->second;
}

void UriTexturePackage::StoreTexture(const nb::System::String &uri, Texture2D *texture)
{
	if(Check(uri))
		return;
	m_mapUris[uri] = texture;
}

void UriTexturePackage::Remove(const nb::System::String &uri)
{
	std::map<nb::System::String, Texture2D *>::iterator iterFind = m_mapUris.find(uri);
	if(iterFind != m_mapUris.end())
		m_mapUris.erase(iterFind);
}

bool UriTexturePackage::Check(const nb::System::String &uri) const
{
	std::map<nb::System::String, Texture2D *>::const_iterator iterFind = m_mapUris.find(uri);
	return iterFind != m_mapUris.end();
}
