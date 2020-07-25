#pragma once
#include "newbrush/core/Object.h"
#include "newbrush/core/Point.h"
#include "newbrush/core/Rect.h"
#include "newbrush/core/media/Pen.h"
#include "newbrush/core/media/ImageSource.h"

namespace nb {
	
class Camera;
class Renderer;
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

	std::shared_ptr<Camera> m_camera;
	std::vector<std::shared_ptr<Renderer>> m_renderers;
	friend class Window;
};

using DrawingContextPtr = std::shared_ptr<DrawingContext>;
}