#include "newbrush/gui/Model3D.h"
#include "newbrush/core/DependencyProperty.h"

using namespace nb;

DependencyPropertyPtr Model3D::TransformProperty()
{
	return DependencyPropertyPtr();
}

DependencyPropertyPtr Model3DGroup::ChildrenProperty()
{
	static auto dp = DependencyProperty::registerDependency<Model3DGroup, Model3DCollectionPtr>("Children", nullptr);
	return dp;
}

DependencyPropertyPtr Mesh3D::PositionsProperty()
{
	static auto dp = DependencyProperty::registerDependency<Model3DGroup, Vec3CollectionPtr>("Positions", nullptr);
	return dp;
}

DependencyPropertyPtr Mesh3D::TextureCoordinatesProperty()
{
	static auto dp = DependencyProperty::registerDependency<Model3DGroup, Vec2CollectionPtr>("TextureCoordinates", nullptr);
	return dp;
}

DependencyPropertyPtr Mesh3D::TriangleIndicesProperty()
{
	static auto dp = DependencyProperty::registerDependency<Model3DGroup, Int16CollectionPtr>("TriangleIndices", nullptr);
	return dp;
}

DependencyPropertyPtr Mesh3D::NormalsProperty()
{
	static auto dp = DependencyProperty::registerDependency<Model3DGroup, Vec3CollectionPtr>("Normals", nullptr);
	return dp;
}

DependencyPropertyPtr Mesh3D::MaterialProperty()
{
	return DependencyPropertyPtr();
}
