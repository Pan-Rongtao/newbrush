#include "newbrush/gui/Path.h"
#include "newbrush/core/MetaObject.h"

using namespace nb;

std::shared_ptr<MetaObject> Path::getMetaObject()
{
	auto meta = MetaObject::get<Path, Shape>("形状", "Path", "轨迹，形状的一种，可描述任意开口路径。", [] {return std::make_shared<Path>(); });
	return meta;
}
