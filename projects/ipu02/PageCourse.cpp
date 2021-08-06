#include "PageCourse.h"

PageCourse::PageCourse(const Rect &rc, NBPageID id)
	: PageBase(rc, id)
{
	init();
}
PageCourse::PageCourse(float x, float y, float w, float h, NBPageID id)
	: PageBase(x, y, w, h, id)
{
	init();
}

void PageCourse::init()
{
	PageBase::init();
	//PageBase::init();
	//To Do the followings:
	//1. init Nodes
	//2. build DataTree
	//3. Others
	clearChildren();
	m_currentid = ID_WELCOME;
	setBackground(SolidColorBrush::ghostWhite());

	m_txttitle = createRef<TextBlock>(u8" 欢迎使用记忆泊车 ");
	m_txttitle->setText(u8"欢迎使用记忆泊车");
	m_txttitle->setColor(Color(0, 0, 0, 255));
	m_txttitle->setPosition(Point(820.0f, 166.0f));
	addChild(m_txttitle);

	m_txtbrief = createRef<TextBlock>(u8" 记忆泊车介绍记忆泊车介绍记忆泊车介绍 ");
	m_txtbrief->setText(u8" 记忆泊车介绍记忆泊车介绍记忆泊车介绍 ");
	m_txtbrief->setColor(Color(0, 0, 0, 255));
	m_txtbrief->setPosition(Point(142.0f, 294.0f));
	addChild(m_txtbrief);


	m_btnskipbg = createRef<Node2D>(142.0f, 168.0f, 160.0f, 56.0f);
	auto texskipbg = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_56px_nor_1.png");
	m_btnskipbg->setBackground(createRef<ImageBrush>(texskipbg));
	m_txtskip = createRef<TextBlock>(u8" 跳过 ");
	m_txtskip->setColor(Color(0, 0, 0, 255));
	m_txtskip->setPosition(Point(190.0f, 180.0f));
	m_btnskip = createRef<Button>(142.0f, 168.0f, 160.0f, 56.0f);
	m_btnskip->Click += nbBindEventFunction(PageCourse::onBtnClicked);
	addChild(m_btnskipbg);
	addChild(m_txtskip);
	addChild(m_btnskip);

	m_courseright = createRef<Node2D>(908.0f, 294.0f, 870.0f, 536.0f);
	auto courserightpbg = TextureLibrary::getFrameFromTextureAtlas("memory", "Course_Right.png");
	m_courseright->setBackground(createRef<ImageBrush>(courserightpbg));
	addChild(m_courseright);

	auto texdotselect = TextureLibrary::getFrameFromTextureAtlas("memory", "ic_piont_p.png");
	auto texdotnoselect = TextureLibrary::getFrameFromTextureAtlas("memory", "ic_piont_n.png");
	m_dotselect = createRef<Node2D>(888.0f, 906.0f, 12.0f, 12.0f);
	m_dotselect->setBackground(createRef<ImageBrush>(texdotselect));
	m_dotnoselect1 = createRef<Node2D>(888.0f, 906.0f, 12.0f, 12.0f);
	m_dotnoselect1->setBackground(createRef<ImageBrush>(texdotnoselect));	
	m_dotnoselect2 = createRef<Node2D>(888.0f, 906.0f, 12.0f, 12.0f);
	m_dotnoselect2->setBackground(createRef<ImageBrush>(texdotnoselect));	
	m_dotnoselect3 = createRef<Node2D>(888.0f, 906.0f, 12.0f, 12.0f);
	m_dotnoselect3->setBackground(createRef<ImageBrush>(texdotnoselect));	
	m_dotnoselect4 = createRef<Node2D>(888.0f, 906.0f, 12.0f, 12.0f);
	m_dotnoselect4->setBackground(createRef<ImageBrush>(texdotnoselect));
	addChild(m_dotselect);
	addChild(m_dotnoselect1);
	addChild(m_dotnoselect2);
	addChild(m_dotnoselect3);
	addChild(m_dotnoselect4);

	m_btnstartbg = createRef<Node2D>(142.0f, 519.0f, 200.0f, 62.0f);
	auto texstartbg = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_62px_sel.png");
	m_btnstartbg->setBackground(createRef<ImageBrush>(texstartbg));	
	m_txtstart = createRef<TextBlock>(u8"开始使用");
	m_txtstart->setColor(Color(255, 255, 255, 255));
	m_txtstart->setPosition(Point(182.0f, 532.0f));	
	m_btnstart = createRef<Button>(142.0f, 519.0f, 200.0f, 62.0f);
	m_btnstart->Click += nbBindEventFunction(PageCourse::onBtnClicked);
	addChild(m_btnstartbg);
	addChild(m_txtstart);
	addChild(m_btnstart);

	m_btnvideoplay = Button::createWithTextureFrameName("memory", "video_btn_play_nor.png", true, 1299.0f, 518.0f);
	m_btnvideoplay->Click += nbBindEventFunction(PageCourse::onBtnClicked);
	addChild(m_btnvideoplay);

	m_texbtnvideostop = TextureLibrary::getFrameFromTextureAtlas("memory", "video_btn_suspend_nor.png");

	welcome();
}

void PageCourse::onBtnClicked(const EventArgs &arg)
{
	if (arg.sender == m_btnskip.get())
	{
		onTriggerSwitchPage(this, NBPageID::NB_PAGEID_MEMORY_PARKING_ROUTE_SELECTION);
	}
	else if (arg.sender == m_btnstart.get())
	{
		onTriggerSwitchPage(this, NBPageID::NB_PAGEID_MEMORY_PARKING_ROUTE_SELECTION);
	}
	else if (arg.sender == m_btnvideoplay.get())
	{
		if (m_btnvideoplay->isChecked())
		{
			m_btnvideoplay->setBkgndNormal(createRef<ImageBrush>(m_texbtnvideostop));
		}		
	}
}

void PageCourse::onTouch(const TouchEventArgs & e)
{
	if (e.action != TouchActionE::down)
		return;
	switch (m_currentid)
	{
	case ID_WELCOME:
		m_currentid = ID_ROUTELEARN;
		routelearn();
		break;
	case ID_ROUTELEARN:
		m_currentid = ID_STARTFROMCAR;
		startfromcar();
		break;
	case ID_STARTFROMCAR:
		m_currentid = ID_STARTFROMPHONE;
		startfromphone();
		break;
	case ID_STARTFROMPHONE:
		m_currentid = ID_COURSEVIDEO;
		coursevideo();
		break;
	case ID_COURSEVIDEO:
		m_currentid = ID_COURSEVIDEO;
		coursevideo();
		break;
	default:
		;
	}
}

void PageCourse::welcome()
{
	m_txttitle->setText(u8"欢迎使用记忆泊车");
	m_txttitle->setColor(Color(0, 0, 0, 255));
	m_txttitle->setPosition(Point(820.0f, 166.0f));
	m_txtbrief->setText(u8"记忆泊车介绍记忆泊车介绍记忆泊车介绍");
	m_txtbrief->setColor(Color(0, 0, 0, 255));
	m_txtbrief->setPosition(Point(142.0f, 294.0f));
	m_dotselect->setPosition(Point(888.0f, 906.0f));
	m_dotnoselect1->setPosition(Point(920.0f, 906.0f));
	m_dotnoselect2->setPosition(Point(956.0f, 906.0f));
	m_dotnoselect3->setPosition(Point(988.0f, 906.0f));
	m_dotnoselect4->setPosition(Point(1020.0f, 906.0f));
	m_btnstartbg->setVisibility(VisibilityE::Hidden);
	m_txtstart->setVisibility(VisibilityE::Hidden);
	m_btnstart->setVisibility(VisibilityE::Hidden);
	m_btnvideoplay->setVisibility(VisibilityE::Hidden);
}

void PageCourse::routelearn()
{
	m_txttitle->setText(u8"路径学习");
	m_txttitle->setColor(Color(0, 0, 0, 255));
	m_txttitle->setPosition(Point(820.0f, 166.0f));
	
	m_txtbrief->setText(u8"路径学习文本路径学习文本路径学习文本");
	m_txtbrief->setColor(Color(0, 0, 0, 255));
	m_txtbrief->setPosition(Point(142.0f, 294.0f));
	m_dotnoselect1->setPosition(Point(888.0f, 906.0f));
	m_dotselect->setPosition(Point(920.0f, 906.0f));
	m_dotnoselect2->setPosition(Point(956.0f, 906.0f));
	m_dotnoselect3->setPosition(Point(988.0f, 906.0f));
	m_dotnoselect4->setPosition(Point(1020.0f, 906.0f));
	m_btnstartbg->setVisibility(VisibilityE::Hidden);
	m_txtstart->setVisibility(VisibilityE::Hidden);
	m_btnstart->setVisibility(VisibilityE::Hidden);
	m_btnvideoplay->setVisibility(VisibilityE::Hidden);
}

void PageCourse::startfromcar()
{
	m_txttitle->setText(u8"从车机端启动记忆泊车");
	m_txttitle->setColor(Color(0, 0, 0, 255));
	m_txttitle->setPosition(Point(820.0f, 166.0f));
	m_txtbrief->setText(u8"从车内启动记忆泊车文本");
	m_txtbrief->setColor(Color(0, 0, 0, 255));
	m_txtbrief->setPosition(Point(142.0f, 294.0f));
	m_dotnoselect2->setPosition(Point(888.0f, 906.0f));
	m_dotnoselect1->setPosition(Point(920.0f, 906.0f));
	m_dotselect->setPosition(Point(956.0f, 906.0f));
	m_dotnoselect3->setPosition(Point(988.0f, 906.0f));
	m_dotnoselect4->setPosition(Point(1020.0f, 906.0f));
	m_btnstartbg->setVisibility(VisibilityE::Hidden);
	m_txtstart->setVisibility(VisibilityE::Hidden);
	m_btnstart->setVisibility(VisibilityE::Hidden);
	m_btnvideoplay->setVisibility(VisibilityE::Hidden);
}

void PageCourse::startfromphone()
{
	m_txttitle->setText(u8"从手机端启动记忆泊车");
	m_txttitle->setColor(Color(0, 0, 0, 255));
	m_txttitle->setPosition(Point(820.0f, 166.0f));
	m_txtbrief->setText(u8"从手机端启动记忆泊车文本");
	m_txtbrief->setColor(Color(0, 0, 0, 255));
	m_txtbrief->setPosition(Point(142.0f, 294.0f));
	m_dotnoselect3->setPosition(Point(888.0f, 906.0f));
	m_dotnoselect1->setPosition(Point(920.0f, 906.0f));
	m_dotnoselect2->setPosition(Point(956.0f, 906.0f));
	m_dotselect->setPosition(Point(988.0f, 906.0f));
	m_dotnoselect4->setPosition(Point(1020.0f, 906.0f));
	m_btnstartbg->setVisibility(VisibilityE::Hidden);
	m_txtstart->setVisibility(VisibilityE::Hidden);
	m_btnstart->setVisibility(VisibilityE::Hidden);
	m_btnvideoplay->setVisibility(VisibilityE::Hidden);
}

void PageCourse::coursevideo()
{
	m_txttitle->setText(u8"记忆泊车教程视频");
	m_txttitle->setColor(Color(0, 0, 0, 255));
	m_txttitle->setPosition(Point(820.0f, 166.0f));
	m_txtbrief->setText(u8"记忆泊车教程视频文本");
	m_txtbrief->setColor(Color(0, 0, 0, 255));
	m_txtbrief->setPosition(Point(142.0f, 294.0f));
	m_dotnoselect4->setPosition(Point(888.0f, 906.0f));
	m_dotnoselect1->setPosition(Point(920.0f, 906.0f));
	m_dotnoselect2->setPosition(Point(956.0f, 906.0f));
	m_dotnoselect3->setPosition(Point(988.0f, 906.0f));
	m_dotselect->setPosition(Point(1020.0f, 906.0f));
	m_btnstartbg->setVisibility(VisibilityE::Visible);
	m_txtstart->setVisibility(VisibilityE::Visible);
	m_btnstart->setVisibility(VisibilityE::Visible);
	m_btnvideoplay->setVisibility(VisibilityE::Visible);
}