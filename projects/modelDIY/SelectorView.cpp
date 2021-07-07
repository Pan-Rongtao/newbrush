#include "SelectorView.h"
#include "MainView.h"

SelectorView::SelectorView()
{
	setWidth(1920.0f);
	setHeight(720.0f);

	setBackground(SolidColorBrush::white());

	auto texFrame = TextureLibrary::getFrameFromTextureAtlas("modelDIY", "bg_640.png");

	auto stage = Node2D::createWithTextureFrameName("modelDIY", "bg_640.png", true, 0.0f, 0.0f);

	m_btnBackToHome = Button::createWithTextureFrameName("modelDIY", "close_96_n.png", true, 24.0f, 24.0f);
	m_btnBackToHome->setBkgndPress(createRef<ImageBrush>("modelDIY", "close_96_p.png"));
	m_btnBackToHome->Click += nbBindEventFunction(SelectorView::onBtnClick);
	m_btnEdit = Button::createWithTextureFrameName("modelDIY", "editor_96_n.png", true, 24.0f, 144.0f);
	m_btnEdit->setBkgndPress(createRef<ImageBrush>("modelDIY", "editor_96_p.png"));
	m_btnEdit->setVisibility(VisibilityE::Hidden);
	m_btnEdit->Click += nbBindEventFunction(SelectorView::onBtnClick);
	m_btnDIYMode = Button::createWithTextureFrameName("modelDIY", "figure_choose_voice_image_female_n.png", true, 830.0f, 152.0f);
	m_btnDIYMode->setBkgndCheck(createRef<ImageBrush>("modelDIY", "figure_choose_voice_image_female_p.png"));
	m_btnDIYMode->Click += nbBindEventFunction(SelectorView::onBtnClick);
	m_btnXiMode = Button::createWithTextureFrameName("modelDIY", "figure_choose_xiaov_n.png", true, 1370.0f, 152.0f);
	m_btnXiMode->setBkgndCheck(createRef<ImageBrush>("modelDIY", "figure_choose_xiaov_p.png"));
	m_btnXiMode->Click += nbBindEventFunction(SelectorView::onBtnClick);

	auto txtDiy = createRef<TextBlock>(920.0f, 532.0f, 180.0f, 36.0f);
	txtDiy->setText(u8"自定义形象");
	auto txtXi = createRef<TextBlock>(1514.0f, 532.0f, 180.0f, 36.0f);
	txtXi->setText(u8"小威");

	addChild(stage);
	addChild(m_btnBackToHome);
	addChild(m_btnEdit);
	addChild(m_btnDIYMode);
	addChild(m_btnXiMode);
	addChild(txtDiy);
	addChild(txtXi);
}

void SelectorView::selectMode(ModelMode mode)
{
	if (m_curMode == mode)
		return;

	switch (mode)
	{
	case ModelMode::Diy:
	{
		m_btnXiMode->setCheck(false);
		m_btnDIYMode->setCheck(!m_btnDIYMode->isChecked());
		m_btnEdit->setVisibility(VisibilityE::Visible);
		MainView::get()->modelNode->load(ModelType::DIY);
		MainView::get()->modelNode->setHorizontalAlignment(HorizontalAlignmentE::Left);
	}
		break;
	case ModelMode::XiaoXi:
	{
		m_btnDIYMode->setCheck(false);
		m_btnXiMode->setCheck(!m_btnXiMode->isChecked());
		m_btnEdit->setVisibility(VisibilityE::Hidden);
		MainView::get()->modelNode->load(ModelType::XiaoV);
		MainView::get()->modelNode->setHorizontalAlignment(HorizontalAlignmentE::Left);
	}
		break;
	default:
		break;
	}
	m_curMode = mode;
}

void SelectorView::onBtnClick(const EventArgs & e)
{
	if (e.sender == m_btnBackToHome.get())
	{
		MainView::get()->switchView(ViewE::Home);
	}
	else if (e.sender == m_btnEdit.get())
	{
		MainView::get()->switchView(ViewE::DIY);
	}
	else if (e.sender == m_btnDIYMode.get())
	{
		selectMode(ModelMode::Diy);
	}
	else if (e.sender == m_btnXiMode.get())
	{
		selectMode(ModelMode::XiaoXi);
	}
}
