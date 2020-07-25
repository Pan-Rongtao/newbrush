#pragma once
#include "newbrush/core/media/Brush.h"

namespace nb {

class NB_API EffectBrush : public Brush
{

};

using EffectBrushPtr = std::shared_ptr<EffectBrush>;
}