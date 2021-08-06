#pragma once

#include "PageBase.h"

using namespace nb;

enum CourseID
{
	ID_WELCOME = 0,
	ID_ROUTELEARN,
	ID_STARTFROMCAR,
	ID_STARTFROMPHONE,
	ID_COURSEVIDEO,
};

class PageCourse : public PageBase
{
	using PageBase::PageBase;
public:
	PageCourse(const Rect &rc, NBPageID id);
	PageCourse(float x, float y, float w, float h, NBPageID id);
	void onBtnClicked(const EventArgs &arg);
	void onTouch(const TouchEventArgs & e);
protected:
	void init();

private:
	void welcome();
	void routelearn();
	void startfromcar();
	void startfromphone();
	void coursevideo();


	ref<Node2D> m_btnskipbg;
	ref<TextBlock> m_txtskip;
	ref<Button> m_btnskip;

	ref<Node2D> m_courseright;

	ref<TextBlock> m_txttitle;
	ref<TextBlock> m_txtbrief;

	ref<Node2D> m_dotselect;
	ref<Node2D> m_dotnoselect1;
	ref<Node2D> m_dotnoselect2;
	ref<Node2D> m_dotnoselect3;
	ref<Node2D> m_dotnoselect4;

	ref<Node2D> m_btnstartbg;
	ref<TextBlock> m_txtstart;
	ref<Button> m_btnstart;

	ref<Button> m_btnvideoplay;
	TextureFrame m_texbtnvideostop;

	CourseID m_currentid;
};