#pragma once

#include "PageBase.h"

using namespace nb;

class PageClaim : public PageBase
{
public:
	PageClaim(const Rect &rc, NBPageID id);
	PageClaim(float x, float y, float w, float h, NBPageID id);
	void onBtnClicked(const EventArgs &arg);
protected:
	void init();

private:
	ref<Button> m_btncheck;

	ref<Node2D> m_btnagreebg;
	ref<TextBlock> m_txtagree;
	ref<Button> m_btnagree;
};