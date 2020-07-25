#pragma once
#include "newbrush/core/media/Brush.h"

namespace nb {

enum class AlignmentXE
{
	Left,
	Center,
	Right,
};

enum class AlignmentYE
{
	Top,
	Center,
	Bottom,
};

enum class TileModeE
{
	None,
	FlipX,
	FlipY,
	FlipXY,
	Tile,
};

enum class BrushMappingModeE
{
	Absolute,
	RelativeToBoundingBox,
};

class TileBrush : public Brush
{
public:
	static DependencyPropertyPtr AligmentXProperty();
	static DependencyPropertyPtr AligmentYProperty();
	static DependencyPropertyPtr StretchProperty();
	static DependencyPropertyPtr TileModeProperty();
	static DependencyPropertyPtr ViewboxProperty();
	static DependencyPropertyPtr ViewportProperty();
	static DependencyPropertyPtr ViewboxUnitsProperty();
	static DependencyPropertyPtr ViewportUnitsProperty();

protected:
	TileBrush() = default;

};

using TileBrushPtr = std::shared_ptr<TileBrush>;
}