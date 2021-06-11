#include "DIYView.h"
#include "MainView.h"

void Page::add(ref<Button> btn)
{
	btn->Click += nbBindEventFunction(onBtnClick);
	addChild(btn);
}

void Page::select(int index)
{
	nbThrowExceptionIf(index >= (int)childCount(), std::out_of_range, "index[%d] is out of range[0, %d)", (int)index, (int)childCount());
	for (auto child : children())
		as<Button>(child)->setCheck(false);
	as<Button>(getChildAt(index))->setCheck(true);
	if (index != m_curCheck)
	{
		m_curCheck = index;
		SelectChangedEventArgs e;
		e.sender = this;
		e.index = m_curCheck;
		SelectChanged.invoke(e);
	}
}

void Page::onBtnClick(const EventArgs &e)
{
	for (auto i = 0; i != childCount(); ++i)
	{
		if (e.sender == getChildAt(i).get())
		{
			select(i);
		}
	}
}

std::vector<std::vector<std::string>> m_Faces =
{
	{ "Face" },
	{ "Face_Fat" },
	{ "Face_thin" },
};
std::vector<std::vector<std::string>> m_Hairs =
{
	{ "hair_Ce" },
	{ "Standard_Gai", "polySurface18", "polySurface10" },
	{ "F_HAIR_264" },
	{ "ZhongFen" },
	{ "WanZi" },
	{ "ZhaMao",  "GLASSES" },
	{ "F_HAIR_238" },
};

std::vector<std::vector<std::string>> m_Eyes =
{
	{ "pSphere5", "pSphere8" },
	{ "XinXing"},
	{ "Smile"},
};

std::vector<std::vector<std::string>> m_Mouth =
{
	{ "Mouth_close" },
	{ "polySurface405", "polySurface403", "polySurface407", "polySurface406", "polySurface408" },
	{ "Mouth_HaHa1" },
};

std::vector<std::vector<std::string>> m_Clothes =
{
	{ "YiFu_D_ChangKu" },
	{ "YiFu_E_QunZi" },
	{ "MN_TOP_1", "DSMK_BTM_004" },
	{ "YiFu_F_TiaoWen" },
	{ "polySurface9", "NeiYi" },
	{ "YiFu_B_XiFu" },
};

std::vector<std::vector<std::string>> m_Shoes =
{
	{ "polySurface397", "polySurface398" },
	{ "polySurface401", "polySurface402" },
	{ "group2", "group3", "group5", "group6" },
	{ "polySurface226", "polySurface227" },
	{ "polySurface265", "polySurface266" },
	{ "polySurface229", "polySurface399" },
};

DIYView::DIYView()
{
	setWidth(1920.0f);
	setHeight(720.0f);
	setAlignmentCenter();
	setBackground(createRef<SolidColorBrush>(Color(231, 231, 245)));
	////////////////
	m_stageBkg = Node2D::createWithTextureFrameName("modelDIY", "change_bg.png", true, 0.0f, 0.0f);
	m_btnBack = Button::createWithTextureFrameName("modelDIY", "go_back_96_n.png", true, 24.0f, 24.0f);
	m_btnBack->setBkgndPress(createRef<ImageBrush>("modelDIY", "go_back_96_p.png"));
	m_btnBack->Click += nbBindEventFunction(onBtnClick);

	auto panel = Node2D::createWithTextureFrameName("modelDIY", "bg_96_192.png", true, 24.0f, 145.0f);
	m_btnBackToGraphics = Button::createWithTextureFrameName("modelDIY", "back_to_graphics_96_n.png", true, 0.0f, 0.0f);
	m_btnBackToGraphics->setBkgndPress(createRef<ImageBrush>("modelDIY", "back_to_graphics_96_p.png"));
	m_btnReset = Button::createWithTextureFrameName("modelDIY", "reset_graphics_96_n.png", true, 0.0f, 96.0f);
	m_btnReset->setBkgndPress(createRef<ImageBrush>("modelDIY", "reset_graphics_96_p.png"));
	panel->addChild(m_btnBackToGraphics);
	panel->addChild(m_btnReset);

	m_btnSave = Button::createWithTextureFrameName("modelDIY", "btn_save_n.png", true, 24.0f, 611.0f);
	m_btnSave->setBkgndPress(createRef<ImageBrush>("modelDIY", "btn_save_p.png"));

	m_stageBkg->addChild(m_btnBack);
	//m_stageBkg->addChild(panel);
	//m_stageBkg->addChild(m_btnSave);

	m_editorRoot = createRef<Node2D>(664.0f, 0.0f, 1920.0f - 664.0f, 720.0f);
	float y = 17.0f;
	const float itemHeight = 110.0f;
	const float itemSpace = 5.0f;
	m_btnFace = Button::createWithTextureFrameName("modelDIY", "pinch_face_96_n.png", true, 0.0f, y + (itemHeight + itemSpace) * 0);
	m_btnFace->setBkgndCheck(createRef<ImageBrush>("modelDIY", "pinch_face_96_p.png"));
	m_btnHair = Button::createWithTextureFrameName("modelDIY", "hairstyle_96_n.png", true, 0.0f, y + (itemHeight + itemSpace) * 1);
	m_btnHair->setBkgndCheck(createRef<ImageBrush>("modelDIY", "hairstyle_96_p.png"));
	m_btnEye = Button::createWithTextureFrameName("modelDIY", "eyes_96_n.png", true, 0.0f, y + (itemHeight + itemSpace) * 2);
	m_btnEye->setBkgndCheck(createRef<ImageBrush>("modelDIY", "eyes_96_p.png"));
	m_btnMouth = Button::createWithTextureFrameName("modelDIY", "mouth_96_n.png", true, 0.0f, y + (itemHeight + itemSpace) * 3);
	m_btnMouth->setBkgndCheck(createRef<ImageBrush>("modelDIY", "mouth_96_p.png"));
	m_btnClothes = Button::createWithTextureFrameName("modelDIY", "suit_96_n.png", true, 0.0f, y + (itemHeight + itemSpace) * 4);
	m_btnClothes->setBkgndCheck(createRef<ImageBrush>("modelDIY", "suit_96_p.png"));
	m_btnShoes = Button::createWithTextureFrameName("modelDIY", "shoes_96_n.png", true, 0.0f, y + (itemHeight + itemSpace) * 5);
	m_btnShoes->setBkgndCheck(createRef<ImageBrush>("modelDIY", "shoes_96_p.png"));
	auto sliderBg = Node2D::createWithTextureFrameName("modelDIY", "slider_bg_1112.png", true, 784.0f - 664.0f, 24.0f);
	m_itemsRoot = createRef<Node2D>(784.0f - 664.0f, /*150.0f*/y, 1112.0f, 530.0f);
	//m_itemsRoot->setBackground(SolidColorBrush::red());
	m_editorRoot->addChild(m_btnFace);
	m_editorRoot->addChild(m_btnHair);
	m_editorRoot->addChild(m_btnEye);
	m_editorRoot->addChild(m_btnMouth);
	m_editorRoot->addChild(m_btnClothes);
	m_editorRoot->addChild(m_btnShoes);
	//m_editorRoot->addChild(sliderBg);
	m_editorRoot->addChild(m_itemsRoot);

	m_popRoot = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 720.0f);
	m_popRoot->setBackground(createRef<SolidColorBrush>(Color(0xCC1A1B45)));
	auto popBG = Node2D::createWithTextureFrameName("modelDIY", "pop_690.png", true, 784.0f - 664.0f, 24.0f);
	popBG->setAlignmentCenter();
	m_btnNo = Button::createWithTextureFrameName("modelDIY", "btn_bg174_no_n.png", true, 103.0f, 228.0f);
	m_btnNo->setBkgndPress(createRef<ImageBrush>("modelDIY", "btn_bg174_no_p.png"));
	m_btnYes = Button::createWithTextureFrameName("modelDIY", "btn_bg174_yes_n.png", true, 413.0f, 228.0f);
	m_btnYes->setBkgndPress(createRef<ImageBrush>("modelDIY", "btn_bg174_yes_p.png"));
	m_btnNo->Click += nbBindEventFunction(onBtnClick);
	m_btnYes->Click += nbBindEventFunction(onBtnClick);
	auto txt = createRef<TextBlock>(u8"人物形象已更改，是否保存？");
	txt->setPosition({ 137.0f, 136.0f });
	m_popRoot->addChild(popBG);
	popBG->addChild(txt);
	popBG->addChild(m_btnNo);
	popBG->addChild(m_btnYes);

	addChild(m_stageBkg);
	addChild(m_editorRoot);

	m_btnFace->Click += nbBindEventFunction(onBtnClick);
	m_btnHair->Click += nbBindEventFunction(onBtnClick);
	m_btnEye->Click += nbBindEventFunction(onBtnClick);
	m_btnMouth->Click += nbBindEventFunction(onBtnClick);
	m_btnClothes->Click += nbBindEventFunction(onBtnClick);
	m_btnShoes->Click += nbBindEventFunction(onBtnClick);

	swithPage(PageE::Face);
	showPop(false);

}

void DIYView::initDresses()
{
	setFace(0);
	setHair(1);
	setEye(0);
	setMouth(2);
	setClothes(4);
	setShoes(2);
}

void DIYView::swithPage(PageE page)
{
	if (m_page == page)	return;

	m_btnFace->setCheck(false);
	m_btnHair->setCheck(false);
	m_btnEye->setCheck(false);
	m_btnMouth->setCheck(false);
	m_btnClothes->setCheck(false);
	m_btnShoes->setCheck(false);

	m_itemsRoot->clearChildren();
	Size itemSize(200.0f, 220.0f);
	switch (page)
	{
	case PageE::Face:
	{
		if (!m_pageFace)
		{
			m_pageFace = createRef<Page>();
			auto btn0 = Button::createWithTextureFrameName("modelDIY", "parts_face_01.png", true, itemSize.width * 0, 0.0f);
			btn0->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_face_01_s.png"));
			auto btn1 = Button::createWithTextureFrameName("modelDIY", "parts_face_02.png", true, itemSize.width * 1, 0.0f);
			btn1->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_face_02_s.png"));
			auto btn2 = Button::createWithTextureFrameName("modelDIY", "parts_face_03.png", true, itemSize.width * 2, 0.0f);
			btn2->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_face_03_s.png"));
			m_pageFace->add(btn0);
			m_pageFace->add(btn1);
			m_pageFace->add(btn2);
			m_pageFace->SelectChanged += nbBindEventFunction(onPageItemSelect);
			m_pageFace->select(0);
		}
		m_itemsRoot->addChild(m_pageFace);
		m_btnFace->setCheck(true);
	}
	break;
	case PageE::Hair:
	{
		if (!m_pageHair)
		{
			m_pageHair = createRef<Page>();
			auto btn0 = Button::createWithTextureFrameName("modelDIY", "parts_hairstyle_01.png", true, itemSize.width * 0, 0.0f);
			btn0->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_hairstyle_01_s.png"));
			auto btn1 = Button::createWithTextureFrameName("modelDIY", "parts_hairstyle_02.png", true, itemSize.width * 1, 0.0f);
			btn1->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_hairstyle_02_s.png"));
			auto btn2 = Button::createWithTextureFrameName("modelDIY", "parts_hairstyle_03.png", true, itemSize.width * 2, 0.0f);
			btn2->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_hairstyle_03_s.png"));
			auto btn3 = Button::createWithTextureFrameName("modelDIY", "parts_hairstyle_04.png", true, itemSize.width * 3, 0.0f);
			btn3->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_hairstyle_04_s.png"));
			auto btn4 = Button::createWithTextureFrameName("modelDIY", "parts_hairstyle_05.png", true, itemSize.width * 4, 0.0f);
			btn4->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_hairstyle_05_s.png"));
			auto btn5 = Button::createWithTextureFrameName("modelDIY", "parts_hairstyle_06.png", true, itemSize.width * 0, itemSize.height);
			btn5->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_hairstyle_06_s.png"));
			m_pageHair->add(btn0);
			m_pageHair->add(btn1);
			m_pageHair->add(btn2);
			m_pageHair->add(btn3);
			m_pageHair->add(btn4);
			m_pageHair->add(btn5);
			m_pageHair->SelectChanged += nbBindEventFunction(onPageItemSelect);
			m_pageHair->select(0);
		}
		m_itemsRoot->addChild(m_pageHair);
		m_btnHair->setCheck(true);
	}
	break;
	case PageE::Eye:
	{
		if (!m_pageEye)
		{
			m_pageEye = createRef<Page>();
			auto btn0 = Button::createWithTextureFrameName("modelDIY", "parts_eyes_01.png", true, itemSize.width * 0, 0.0f);
			btn0->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_eyes_01_s.png"));
			auto btn1 = Button::createWithTextureFrameName("modelDIY", "parts_eyes_04.png", true, itemSize.width * 1, 0.0f);
			btn1->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_eyes_04_s.png"));
			auto btn2 = Button::createWithTextureFrameName("modelDIY", "parts_eyes_03.png", true, itemSize.width * 2, 0.0f);
			btn2->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_eyes_03_s.png"));
			m_pageEye->add(btn0);
			m_pageEye->add(btn1);
			m_pageEye->add(btn2);
			m_pageEye->SelectChanged += nbBindEventFunction(onPageItemSelect);
			m_pageEye->select(0);
		}
		m_itemsRoot->addChild(m_pageEye);
		m_btnEye->setCheck(true);
	}
	break;
	case PageE::Mouth:
	{
		if (!m_pageMouth)
		{
			m_pageMouth = createRef<Page>();
			auto btn0 = Button::createWithTextureFrameName("modelDIY", "parts_mouth_01.png", true, itemSize.width * 0, 0.0f);
			btn0->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_mouth_01_s.png"));
			auto btn1 = Button::createWithTextureFrameName("modelDIY", "parts_mouth_02.png", true, itemSize.width * 1, 0.0f);
			btn1->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_mouth_02_s.png"));
			auto btn2 = Button::createWithTextureFrameName("modelDIY", "parts_mouth_03.png", true, itemSize.width * 2, 0.0f);
			btn2->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_mouth_03_s.png"));
			m_pageMouth->add(btn0);
			m_pageMouth->add(btn1);
			m_pageMouth->add(btn2);
			m_pageMouth->SelectChanged += nbBindEventFunction(onPageItemSelect);
			m_pageMouth->select(0);
		}
		m_itemsRoot->addChild(m_pageMouth);
		m_btnMouth->setCheck(true);
	}
	break;
	case PageE::Clothes:
	{
		if (!m_pageClothes)
		{
			m_pageClothes = createRef<Page>();
			auto btn0 = Button::createWithTextureFrameName("modelDIY", "parts_suit_01.png", true, itemSize.width * 0, 0.0f);
			btn0->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_suit_01_s.png"));
			auto btn1 = Button::createWithTextureFrameName("modelDIY", "parts_suit_02.png", true, itemSize.width * 1, 0.0f);
			btn1->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_suit_02_s.png"));
			auto btn2 = Button::createWithTextureFrameName("modelDIY", "parts_suit_03.png", true, itemSize.width * 2, 0.0f);
			btn2->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_suit_03_s.png"));
			auto btn3 = Button::createWithTextureFrameName("modelDIY", "parts_suit_04.png", true, itemSize.width * 3, 0.0f);
			btn3->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_suit_04_s.png"));
			auto btn4 = Button::createWithTextureFrameName("modelDIY", "parts_suit_05.png", true, itemSize.width * 4, 0.0f);
			btn4->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_suit_05_s.png"));
			auto btn5 = Button::createWithTextureFrameName("modelDIY", "parts_suit_06.png", true, itemSize.width * 0, itemSize.height);
			btn5->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_suit_06_s.png"));
			m_pageClothes->add(btn0);
			m_pageClothes->add(btn1);
			m_pageClothes->add(btn2);
			m_pageClothes->add(btn3);
			m_pageClothes->add(btn4);
			m_pageClothes->add(btn5);
			m_pageClothes->SelectChanged += nbBindEventFunction(onPageItemSelect);
			m_pageClothes->select(0);
		}
		m_itemsRoot->addChild(m_pageClothes);
		m_btnClothes->setCheck(true);
	}
	break;
	case PageE::Shoes:
	{
		if (!m_pageShoes)
		{
			m_pageShoes = createRef<Page>();
			auto btn0 = Button::createWithTextureFrameName("modelDIY", "parts_shoes_01.png", true, itemSize.width * 0, 0.0f);
			btn0->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_shoes_01_s.png"));
			auto btn1 = Button::createWithTextureFrameName("modelDIY", "parts_shoes_02.png", true, itemSize.width * 1, 0.0f);
			btn1->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_shoes_02_s.png"));
			auto btn2 = Button::createWithTextureFrameName("modelDIY", "parts_shoes_03.png", true, itemSize.width * 2, 0.0f);
			btn2->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_shoes_03_s.png"));
			auto btn3 = Button::createWithTextureFrameName("modelDIY", "parts_shoes_04.png", true, itemSize.width * 3, 0.0f);
			btn3->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_shoes_04_s.png"));
			auto btn4 = Button::createWithTextureFrameName("modelDIY", "parts_shoes_05.png", true, itemSize.width * 4, 0.0f);
			btn4->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_shoes_05_s.png"));
			auto btn5 = Button::createWithTextureFrameName("modelDIY", "parts_shoes_06.png", true, itemSize.width * 0, itemSize.height);
			btn5->setBkgndCheck(createRef<ImageBrush>("modelDIY", "parts_shoes_06_s.png"));
			m_pageShoes->add(btn0);
			m_pageShoes->add(btn1);
			m_pageShoes->add(btn2);
			m_pageShoes->add(btn3);
			m_pageShoes->add(btn4);
			m_pageShoes->add(btn5);
			m_pageShoes->SelectChanged += nbBindEventFunction(onPageItemSelect);
			m_pageShoes->select(0);
		}
		m_itemsRoot->addChild(m_pageShoes);
		m_btnShoes->setCheck(true);
	}
	break;
	default:
		break;
	}
	m_page = page;
}

void DIYView::setComponent(std::vector<std::vector<std::string>> meshes, int index)
{
	auto model = MainView::get()->modelNode->getModel();
	for (auto i = 0; i != meshes.size(); ++i)
	{
		auto meshNames = meshes[i];
		for (auto j = 0; j != meshNames.size(); ++j)
		{
			model->setRenderAble(meshNames[j], i == index);
		}
	}
}

void DIYView::setFace(int index)
{
	setComponent(m_Faces, index);
}

void DIYView::setHair(int index)
{
	setComponent(m_Hairs, index);
}

void DIYView::setEye(int index)
{
	setComponent(m_Eyes, index);
}

void DIYView::setMouth(int index)
{
	setComponent(m_Mouth, index);
}

void DIYView::setClothes(int index)
{
	setComponent(m_Clothes, index);
}

void DIYView::setShoes(int index)
{
	setComponent(m_Shoes, index);
}

void DIYView::onBtnClick(const EventArgs & e)
{
	if (e.sender == m_btnBack.get())
	{
		MainView::get()->switchView(ViewE::Selector);
	}
	else if (e.sender == m_btnFace.get())
	{
		swithPage(PageE::Face);
	}
	else if (e.sender == m_btnHair.get())
	{
		swithPage(PageE::Hair);
	}
	else if (e.sender == m_btnEye.get())
	{
		swithPage(PageE::Eye);
	}
	else if (e.sender == m_btnMouth.get())
	{
		swithPage(PageE::Mouth);
	}
	else if (e.sender == m_btnClothes.get())
	{
		swithPage(PageE::Clothes);
	}
	else if (e.sender == m_btnShoes.get())
	{
		swithPage(PageE::Shoes);
	}
	else if (e.sender == m_btnNo.get())
	{
		showPop(false);
	}
	else if (e.sender == m_btnYes.get())
	{
		showPop(false);
	}
}

void DIYView::onPageItemSelect(const Page::SelectChangedEventArgs & e)
{
	auto index = e.index;
	auto sender = e.sender;
	if (sender == m_pageFace.get())
	{
		setFace(index);
	}
	else if (sender == m_pageHair.get())
	{
		setHair(index);
	}
	else if (sender == m_pageEye.get())
	{
		setEye(index);
	}
	else if (sender == m_pageMouth.get())
	{
		setMouth(index);
	}
	else if (sender == m_pageClothes.get())
	{
		setClothes(index);
	}
	else if (sender == m_pageShoes.get())
	{
		setShoes(index);
	}
}

void DIYView::showPop(bool show)
{
	if (show)
	{
		addChild(m_popRoot);
	}
	else
	{
		removeChild(m_popRoot);
	}
}
