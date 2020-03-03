﻿#include "newbrush/media/ImageSource.h"
#include "newbrush/media/Bitmap.h"

using namespace nb;

ImageSource::ImageSource()
	: ImageSource("")
{
}

ImageSource::ImageSource(const std::string & uri)
{
	auto bm = getValue<std::shared_ptr<Bitmap>>(BmProperty());
	bm->load(uri);
}

float ImageSource::width() const
{
	auto bm = getValue<std::shared_ptr<Bitmap>>(BmProperty());
	return (float)bm->width();
}

float ImageSource::heigth() const
{
	auto bm = getValue<std::shared_ptr<Bitmap>>(BmProperty());
	return (float)bm->height();
}

DependencyProperty ImageSource::BmProperty()
{
	static auto dp = DependencyProperty::registerDependency<ImageSource, std::shared_ptr<Bitmap>>("Bm", std::make_shared<Bitmap>());
	return dp;
}
