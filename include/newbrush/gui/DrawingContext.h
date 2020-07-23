#pragma once
#include "newbrush/core/Object.h"
#include "newbrush/core/Point.h"
#include "newbrush/core/Rect.h"
#include "newbrush/gles/Camera.h"

namespace nb {

class Pen;
class Brush;
class ImageSource;
class Renderer;
class Camera;
using PenPtr = std::shared_ptr<Pen>;
using BrushPtr = std::shared_ptr<Brush>;
using ImageSourcePtr = std::shared_ptr<ImageSource>;
using RendererPtr = std::shared_ptr<Renderer>;
using CameraPtr = std::shared_ptr<Camera>;

class NB_API DrawingContext : public Object
{
public:
	DrawingContext();

	//绘制一条线段
	void drawLine(PenPtr pen, const Point &p0, const Point &p1);

	//绘制一个矩形
	void drawRectangle(BrushPtr brush, PenPtr pen, const Rect &rect);

	//绘制一个圆角矩形
	void drawRoundedRectangle(BrushPtr brush, PenPtr pen, const Rect &rect, float radiusX, float radiusY);

	//绘制一个椭圆
	void drawEllipse(BrushPtr brush, PenPtr pen, const Point &center, float radiusX, float radiusY);

	//绘制图片
	void drawImage(ImageSourcePtr source, const Rect &rect);

	//绘制文本
	void drawText(/*ImageSourcePtr source, FormattedText*/const Point &p);

private:
	void resize(int width, int height);
	void draw();

	CameraPtr m_camera;
	std::vector<RendererPtr> m_renderers;
	friend class Window;
};

}