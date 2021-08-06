#include "PageClaim.h"

PageClaim::PageClaim(const Rect &rc, NBPageID id)
	: PageBase(rc, id)
{
	init();
}
PageClaim::PageClaim(float x, float y, float w, float h, NBPageID id)
	: PageBase(x, y, w, h, id)
{
	init();
}

void PageClaim::init()
{
	//To Do the followings:
	//1. init Nodes
	//2. build DataTree
	//3. Others
	PageBase::init();
	clearChildren();
	auto img = Node2D::createWithTextureFrameName("memory", "autopark_pic2.png");
	addChild(img);

	auto overlay = createRef<Node2D>(0.0f, 704.0f, 1920.0f, 276.0f);
	overlay->setBackground(SolidColorBrush::ghostWhite());
	overlay->setOpacity(0.8);
	addChild(overlay);	

	auto texbtnocheck = TextureLibrary::getFrameFromTextureAtlas("memory", "btn_off_blue.png");
	auto texbtcheck = TextureLibrary::getFrameFromTextureAtlas("memory", "btn_on_blue.png");
	m_btncheck = createRef<Button>(580.0f, 772.0f, 40.0f, 40.0f);
	m_btncheck->setBkgndNormal(createRef<ImageBrush>(texbtnocheck));
	m_btncheck->setBkgndCheck(createRef<ImageBrush>(texbtcheck));
	m_btncheck->Click += nbBindEventFunction(PageClaim::onBtnClicked);
	addChild(m_btncheck);

	auto txt = createRef<TextBlock>(u8" 我已阅读并同意《记忆泊车使用协议》和《数据保护规定》 ");
	txt->setPosition(Point(628.0f,775.0f));
	addChild(txt);	

	m_btnagreebg = createRef<Node2D>(840.0f, 856.0f, 240.0f, 62.0f);
	auto texagreebg = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_62px_sel2.png");
	m_btnagreebg->setBackground(createRef<ImageBrush>(texagreebg));
	addChild(m_btnagreebg);
	m_txtagree = createRef<TextBlock>(u8" 接受并继续 ");
	m_txtagree->setColor(Color(255, 255, 255, 255));
	m_txtagree->setPosition(Point(880.0f, 870.0f));
	addChild(m_txtagree);
	m_btnagree = createRef<Button>(840.0f, 856.0f, 240.0f, 62.0f);
	m_btnagree->Click += nbBindEventFunction(PageClaim::onBtnClicked);
	addChild(m_btnagree);
}

void PageClaim::onBtnClicked(const EventArgs &arg)
{
	if (arg.sender == m_btncheck.get())
	{
		if (m_btncheck->isChecked())
		{
			m_btncheck->setCheck(false);
		}
		else
		{
			m_btncheck->setCheck(true);
		}
	}
	if (arg.sender == m_btnagree.get())
	{	
		onTriggerSwitchPage(this, NBPageID::NB_PAGEID_MEMORY_PARKING_COURSE);
	}
}