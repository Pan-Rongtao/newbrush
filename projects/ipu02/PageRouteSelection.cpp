#include "PageRouteSelection.h"

Card::Card(const Rect &rc, CardType cardtype)
	: Node2D(rc)
	, m_cardtype(cardtype)
{
	auto texcardbg = TextureLibrary::getFrameFromTextureAtlas("memory", "card.png");
	setBackground(createRef<ImageBrush>(texcardbg));
}

Card::Card(float x, float y, float w, float h, CardType cardtype)
	: Node2D(x, y, w, h)
	, m_cardtype(cardtype)
{
	auto texcardbg = TextureLibrary::getFrameFromTextureAtlas("memory", "card.png");
	setBackground(createRef<ImageBrush>(texcardbg));
}

CardType Card::cardtype()
{
	return m_cardtype;
}

void Card::init()
{
}

void Card::onTriggerCardToPage(NBPageID pageid)
{
	CardToPageEventArgs e;
	e.sender = this;
	e.m_pageid = pageid;
	CardToPageEvent.invoke(e);
}

NewCard::NewCard(const Rect &rc, CardType cardtype)
	: Card(rc, cardtype)
{
	auto texcardbg = TextureLibrary::getFrameFromTextureAtlas("memory", "card.png");
	setBackground(createRef<ImageBrush>(texcardbg));
}

NewCard::NewCard(float x, float y, float w, float h, CardType cardtype)
	: Card(x, y, w, h, cardtype)
{
	init();
}

void NewCard::init()
{
	Card::init();

	m_txtcardtitle = createRef<TextBlock>(u8" 创建路线 ");
	m_txtcardtitle->setPosition(Point(150.0f, 139.0f));
	addChild(m_txtcardtitle);

	m_btnrouteinbg = createRef<Node2D>(99.0f, 274.0f, 240.0f, 62.0f);
	auto texrouteinbg = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_62px_nor1.png");
	m_btnrouteinbg->setBackground(createRef<ImageBrush>(texrouteinbg));
	m_txtroutein = createRef<TextBlock>(u8" 入库 ");
	m_txtroutein->setColor(Color(0, 0, 0, 255));
	m_txtroutein->setPosition(Point(180.0f, 285.0f));
	m_btnroutein = createRef<Button>(99.0f, 274.0f, 240.0f, 62.0f);
	m_btnroutein->Click += nbBindEventFunction(NewCard::onBtnClicked);
	addChild(m_btnrouteinbg);
	addChild(m_txtroutein);
	addChild(m_btnroutein);

	m_btnrouteoutbg = createRef<Node2D>(99.0f, 369.0f, 240.0f, 62.0f);
	auto texrouteoutbg = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_62px_nor1.png");
	m_btnrouteoutbg->setBackground(createRef<ImageBrush>(texrouteoutbg));
	m_txtrouteout = createRef<TextBlock>(u8" 出库 ");
	m_txtrouteout->setColor(Color(0, 0, 0, 255));
	m_txtrouteout->setPosition(Point(180.0f, 380.0f));
	m_btnrouteout = createRef<Button>(99.0f, 369.0f, 240.0f, 62.0f);
	m_btnrouteout->Click += nbBindEventFunction(NewCard::onBtnClicked);
	addChild(m_btnrouteoutbg);
	addChild(m_txtrouteout);
	addChild(m_btnrouteout);
}

void NewCard::onBtnClicked(const EventArgs &arg)
{
	if (arg.sender == m_btnroutein.get())
	{
		onTriggerCardToPage(NB_PAGEID_MEMORY_PARKING_IN_NEW_ROUTE);
	}
	else if (arg.sender == m_btnrouteout.get())
	{
		onTriggerCardToPage(NB_PAGEID_MEMORY_PARKING_OUT_NEW_ROUTE);
	}
}

CardCompleted::CardCompleted(const Rect &rc, CardType cardtype)
	: Card(rc, cardtype)
{
	auto texcardbg = TextureLibrary::getFrameFromTextureAtlas("memory", "card.png");
	setBackground(createRef<ImageBrush>(texcardbg));
}

CardCompleted::CardCompleted(float x, float y, float w, float h, CardType cardtype)
	:Card(x, y, w, h, cardtype)
{
	init();
}

void CardCompleted::init()
{
	Card::init();

	m_txtcardtitle = createRef<TextBlock>(u8"温暖的家");
	m_txtcardtitle->setPosition(Point(150.0f, 139.0f));
	addChild(m_txtcardtitle);

	m_txtcardcontent = createRef<TextBlock>(u8"入库|固定车位");
	m_txtcardcontent->setPosition(Point(110.0f, 255.0f));
	addChild(m_txtcardcontent);

	m_btnstartbg = createRef<Node2D>(93.0f, 369.0f, 240.0f, 62.0f);
	auto texstartbg = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_62px_sel2.png");
	m_btnstartbg->setBackground(createRef<ImageBrush>(texstartbg));
	m_txtstart = createRef<TextBlock>(u8"开始使用");
	m_txtstart->setColor(Color(0, 0, 0, 255));
	m_txtstart->setPosition(Point(150.0f, 380.0f));
	m_btnstart = createRef<Button>(93.0f, 369.0f, 240.0f, 62.0f);
	m_btnstart->Click += nbBindEventFunction(CardCompleted::onBtnClicked);
	addChild(m_btnstartbg);
	addChild(m_txtstart);
	addChild(m_btnstart);
}

void CardCompleted::onBtnClicked(const EventArgs &arg)
{
	if (arg.sender == m_btnstart.get())
	{
		onTriggerCardToPage(NB_PAGEID_MEMORY_PARKING_CONDITION_DETECTION);
	}
}

CardFail::CardFail(const Rect &rc, CardType cardtype)
	: Card(rc, cardtype)
{
	auto texcardbg = TextureLibrary::getFrameFromTextureAtlas("memory", "card.png");
	setBackground(createRef<ImageBrush>(texcardbg));
}

CardFail::CardFail(float x, float y, float w, float h, CardType cardtype)
	:Card(x, y, w, h, cardtype)
{
	init();
}

void CardFail::init()
{
	Card::init();

	m_txtcardtitle = createRef<TextBlock>(u8"后台学习失败");
	m_txtcardtitle->setColor(Color(255, 0, 0, 255));
	m_txtcardtitle->setPosition(Point(120.0f, 139.0f));
	addChild(m_txtcardtitle);

	m_txtcardcontent = createRef<TextBlock>(u8"10天后将自动删除");
	m_txtcardcontent->setColor(Color(255, 0, 0, 255));
	m_txtcardcontent->setPosition(Point(90.0f, 255.0f));
	addChild(m_txtcardcontent);

	m_btndeletebg = createRef<Node2D>(93.0f, 369.0f, 240.0f, 62.0f);
	auto texdeletebg = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_62px_warn2.png");
	m_btndeletebg->setBackground(createRef<ImageBrush>(texdeletebg));
	m_txtdelte = createRef<TextBlock>(u8"删除");
	m_txtdelte->setColor(Color(255, 0, 0, 255));
	m_txtdelte->setPosition(Point(180.0f, 380.0f));
	m_btndelete = createRef<Button>(93.0f, 369.0f, 240.0f, 62.0f);
	m_btndelete->Click += nbBindEventFunction(CardFail::onBtnClicked);
	addChild(m_btndeletebg);
	addChild(m_txtdelte);
	addChild(m_btndelete);
}

void CardFail::onBtnClicked(const EventArgs &arg)
{
	if (arg.sender == m_btndelete.get())
	{
		onTriggerCardToPage(NB_PAGEID_MEMORY_PARKING_CONDITION_DETECTION);
	}
}

PageRouteSelection::PageRouteSelection(const Rect &rc, NBPageID id)
	: PageBase(rc, id)
{
	init();
}
PageRouteSelection::PageRouteSelection(float x, float y, float w, float h, NBPageID id)
	: PageBase(x, y, w, h, id)
{
	init();
}


void PageRouteSelection::init()
{
	//To Do the followings:
	//1. init Nodes
	//2. build DataTree
	//3. Others
	PageBase::init();
	clearChildren();
	setBackground(SolidColorBrush::ghostWhite());

	m_txtrouteselect = createRef<TextBlock>(u8" 路线选择 ");
	m_txtrouteselect->setColor(Color(0, 0, 0, 255));
	m_txtrouteselect->setPosition(Point(86.0f, 166.0f));
	addChild(m_txtrouteselect);

	m_btncoursebg = createRef<Node2D>(1660.0f, 166.0f, 180.0f, 56.0f);
	auto texcoursebg = TextureLibrary::getFrameFromTextureAtlas("memory", "autopark_btn_56px_nor.png");
	m_btncoursebg->setBackground(createRef<ImageBrush>(texcoursebg));
	addChild(m_btncoursebg);
	m_btncourseicon = createRef<Node2D>(24.0f, 5.0f, 46.0f, 46.0f);
	auto texcourseiconbg = TextureLibrary::getFrameFromTextureAtlas("memory", "music_search_icon_search.png");
	m_btncourseicon->setBackground(createRef<ImageBrush>(texcourseiconbg));
	m_btncoursebg->addChild(m_btncourseicon);;
	m_txtcourse = createRef<TextBlock>(u8" 教程 ");
	m_txtcourse->setColor(Color(0, 0, 0, 255));
	m_txtcourse->setPosition(Point(82.0f, 10.0f));
	m_btncoursebg->addChild(m_txtcourse);
	m_btncourse = createRef<Button>(1660.0f, 166.0f, 180.0f, 56.0f);
	m_btncourse->Click += nbBindEventFunction(PageRouteSelection::onBtnClicked);	
	addChild(m_btncourse);

	m_newcard = createRef<NewCard>(991,320,437,570,NEWCARD);
	m_newcard->CardToPageEvent += nbBindEventFunction(PageRouteSelection::onCardToPage);
	addChild(m_newcard);

	m_completedcard = createRef<CardCompleted>(77, 320,437, 570, CARDCOMPLETED);
	m_completedcard->CardToPageEvent += nbBindEventFunction(PageRouteSelection::onCardToPage);
	addChild(m_completedcard);

	m_failcard = createRef<CardFail>(534, 320,437, 570, CARDFAIL);
	m_failcard->CardToPageEvent += nbBindEventFunction(PageRouteSelection::onCardToPage);
	addChild(m_failcard);
}

void PageRouteSelection::onBtnClicked(const EventArgs &arg)
{
	if (arg.sender == m_btncourse.get())
	{
		onTriggerSwitchPage(this, NB_PAGEID_MEMORY_PARKING_COURSE);
	}
}

void PageRouteSelection::onCardToPage(const Card::CardToPageEventArgs &args)
{
	onTriggerSwitchPage(this, args.m_pageid);
}