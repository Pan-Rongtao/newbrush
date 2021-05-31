#pragma once
#include "../Common.h"

class Page : public Node2D
{
public:
	void add(ref<Button> btn);
	void select(int index);

	struct SelectChangedEventArgs : public EventArgs { int index; };
	Event<SelectChangedEventArgs> SelectChanged;

private:
	void onBtnClick(const EventArgs &e);

	int m_curCheck{-1};
};

class DIYView : public Node2D
{
public:
	DIYView();

	void initDresses();

	void setFace(int index);
	void setHair(int index);
	void setEye(int index);
	void setMouth(int index);
	void setClothes(int index);
	void setShoes(int index);

private:
	enum class PageE
	{
		None,
		Face,
		Hair,
		Eye,
		Mouth,
		Clothes,
		Shoes,
	};

	void swithPage(PageE page);
	void onBtnClick(const EventArgs &e);
	void onPageItemSelect(const Page::SelectChangedEventArgs &e);
	void showPop(bool show);
	void setComponent(std::vector<std::vector<std::string>> meshes, int index);

	ref<Node2D> m_stageBkg;
	ref<Button> m_btnBack;
	ref<Button> m_btnBackToGraphics;
	ref<Button> m_btnReset;
	ref<Button> m_btnSave;

	ref<Node2D> m_editorRoot;
	ref<Button> m_btnFace;
	ref<Button> m_btnHair;
	ref<Button> m_btnEye;
	ref<Button> m_btnMouth;
	ref<Button> m_btnClothes;
	ref<Button> m_btnShoes;

	ref<Node2D> m_itemsRoot;
	ref<Page> m_pageFace;
	ref<Page> m_pageHair;
	ref<Page> m_pageEye;
	ref<Page> m_pageMouth;
	ref<Page> m_pageClothes;
	ref<Page> m_pageShoes;
	std::array<ref<Button>, 3> m_faceItems;
	std::array<ref<Button>, 3> m_hairItems;
	std::array<ref<Button>, 3> m_eyeItems;
	std::array<ref<Button>, 3> m_mouthItems;
	std::array<ref<Button>, 3> m_clothesItems;
	std::array<ref<Button>, 3> m_shoesItems;

	ref<Node2D> m_popRoot;
	ref<Button> m_btnYes;
	ref<Button> m_btnNo;

	PageE m_page{ PageE::None };
};