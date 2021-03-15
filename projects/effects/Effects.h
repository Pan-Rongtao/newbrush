#pragma once
#include "newbrush/Brush.h"
#include "newbrush/Shader.h"

using namespace nb;

class GaussianBlurMateial : public Material
{
public:
	GaussianBlurMateial(ref<Texture2D> texture, float _intensity);

	virtual void uploadUniform(ref<Camera> camera) override;

	ref<Texture2D> texture0;
	float intensity;
};

class VortexMaterial : public Material
{
public:
	VortexMaterial(ref<Texture2D> texture, float _r, float _angle);

	virtual void uploadUniform(ref<Camera> camera) override;

	ref<Texture2D> texture0;
	float r;
	float angle;
};

class FlameMaterial : public Material
{
public:
	FlameMaterial(ref<Texture2D> texture);
	virtual void uploadUniform(ref<Camera> camera) override;

	ref<Texture2D> texture0;
	float time;
};
