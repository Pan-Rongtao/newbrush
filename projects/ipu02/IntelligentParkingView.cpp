#include "IntelligentParkingView.h"

#include "MainView.h"
#include "ManualParkingView.h"
#include "MemoryParking.h"

ref<TextBlock> g_TxtBack;

IntelligentParkingView::IntelligentParkingView()
	: m_CurState(ID_Unknow)
{
	TextureLibrary::addTextureAtlas("intelligent_day", RES_DIR"ipu02/intelligent_day.png", RES_DIR"ipu02/intelligent_day.txt");
	//TextureLibrary::addTextureAtlas("manual", RES_DIR"ipu02/manual_day.png", RES_DIR"ipu02/manual_day.txt");
	TextureLibrary::addTextureAtlas("extra", RES_DIR"ipu02/intelligent_day_extra.png", RES_DIR"ipu02/intelligent_day_extra.txt");

	m_timerAutoParkingPlayer.Tick += nbBindEventFunction(IntelligentParkingView::onAutoParkingPlayTick);
	
	setBackground(createRef<SolidColorBrush>(Color(238, 240, 245)));

	m_NodeLeftRef = IntelligentParkingLeft::createIntelligentParkingLeftRef(0, 100, 600, 880);
	m_NodeRightRef = IntelligentParkingRight::createIntelligentParkingRightRef(610, 100, 1310, 880);
	m_NodeRemoteCtrlParkingRef = createRef<IntelligentRemoteCtrlParking>();
	
	addChild(m_NodeRemoteCtrlParkingRef);
	addChild(m_NodeLeftRef);
	addChild(m_NodeRightRef);
	m_NodeLeftRef->onEnterMenu(1);
	m_NodeRightRef->SwitchSence(2);

	////////////////////////////////////////////////////////////////////////////////////
	//TopLine
	g_TxtBack = createRef<TextBlock>(u8"退出");
	g_TxtBack->setPosition(Point(104, 39));
	addChild(g_TxtBack);

	auto texFrame = TextureLibrary::getFrameFromTextureAtlas("intelligent_day", "icon_topbar_back.png");
	m_BtnBackImage = createRef<Node2D>(55, 32, texFrame.sourceSize.x, texFrame.sourceSize.y);
	m_BtnBackImage->setBackground(createRef<ImageBrush>(texFrame));
	addChild(m_BtnBackImage);

	m_BtnBack = createRef<Button>(55, 32, 140, 100);//Button::createWithTextureFrameName("intelligent_day", "icon_topbar_back.png", true, 55, 32);
	m_BtnBack->Click += nbBindEventFunction(IntelligentParkingView::onBtnClick);
	m_BtnBack->Touch += [](const TouchEventArgs &e)
	{
		if (e.action == TouchActionE::down)
			g_TxtBack->setColor(Color(Colors::blue));
		if (e.action == TouchActionE::up)
			g_TxtBack->setColor(Color(Colors::black));
	};
	addChild(m_BtnBack);

	/////////////////////////////////////////////////////////////////
	m_TopBtnsRef = createRef<Node2D>();
	texFrame = TextureLibrary::getFrameFromTextureAtlas("extra", "TopSwitchBtnBg.png");
	m_TopBtnsRef = createRef<Node2D>(660, 19, texFrame.sourceSize.x, texFrame.sourceSize.y);
	m_TopBtnsRef->setBackground(createRef<ImageBrush>(texFrame));
	
	m_btnAutoParking = Button::createWithTextureFrameName("extra", "TopSwitchBtn_n.png", true, 2, 2);
	m_btnAutoParking->setBkgndPress(createRef<ImageBrush>("extra", "TopSwitchBtn_s.png"));
	m_btnAutoParking->setBkgndCheck(createRef<ImageBrush>("extra", "TopSwitchBtn_s.png"));
	m_btnAutoParking->Click += nbBindEventFunction(IntelligentParkingView::onSwitchBtnClick);
	m_TopBtnsRef->addChild(m_btnAutoParking);

	m_txtAutoParking = createRef<TextBlock>(u8"自动泊车");
	m_txtAutoParking->setPosition(Point(13, 15));
	m_TopBtnsRef->addChild(m_txtAutoParking);

	m_btnAutoParking->setCheck(true);
	m_txtAutoParking->setColor(Colors::white);

	m_btnCtrlParking = Button::createWithTextureFrameName("extra", "TopSwitchBtn_n.png", true, 166, 2);
	m_btnCtrlParking->setBkgndPress(createRef<ImageBrush>("extra", "TopSwitchBtn_s.png"));
	m_btnCtrlParking->setBkgndCheck(createRef<ImageBrush>("extra", "TopSwitchBtn_s.png"));
	m_btnCtrlParking->Click += nbBindEventFunction(IntelligentParkingView::onSwitchBtnClick);
	m_TopBtnsRef->addChild(m_btnCtrlParking);

	m_txtCtrlParking = createRef<TextBlock>(u8"遥控泊车");
	m_txtCtrlParking->setPosition(Point(182, 15));
	m_TopBtnsRef->addChild(m_txtCtrlParking);

	m_btnSeletParking = Button::createWithTextureFrameName("extra", "TopSwitchBtn_n.png", true, 330, 2);
	m_btnSeletParking->setBkgndPress(createRef<ImageBrush>("extra", "TopSwitchBtn_s.png"));
	m_btnSeletParking->setBkgndCheck(createRef<ImageBrush>("extra", "TopSwitchBtn_s.png"));
	m_btnSeletParking->Click += nbBindEventFunction(IntelligentParkingView::onSwitchBtnClick);
	m_TopBtnsRef->addChild(m_btnSeletParking);

	m_txtSeletParking = createRef<TextBlock>(u8"自选车位");
	m_txtSeletParking->setPosition(Point(346, 15));
	m_TopBtnsRef->addChild(m_txtSeletParking);

	m_btnMemoryParking = Button::createWithTextureFrameName("extra", "TopSwitchBtn_n.png", true, 494, 2);
	m_btnMemoryParking->setBkgndPress(createRef<ImageBrush>("extra", "TopSwitchBtn_s.png"));
	m_btnMemoryParking->setBkgndCheck(createRef<ImageBrush>("extra", "TopSwitchBtn_s.png"));
	m_btnMemoryParking->Click += nbBindEventFunction(IntelligentParkingView::onSwitchBtnClick);
	m_TopBtnsRef->addChild(m_btnMemoryParking);

	m_txtMemoryParking = createRef<TextBlock>(u8"记忆泊车");
	m_txtMemoryParking->setPosition(Point(510, 15));
	m_TopBtnsRef->addChild(m_txtMemoryParking);

	addChild(m_TopBtnsRef);
}

void IntelligentParkingView::onSwitchBtnClick(const EventArgs &e)
{
	m_timerAutoParkingPlayer.stop();

	if (e.sender == m_btnAutoParking.get()){
		m_btnAutoParking->setCheck(true);
		m_btnCtrlParking->setCheck(false);
		m_btnSeletParking->setCheck(false);
		m_btnMemoryParking->setCheck(false);
		m_txtAutoParking->setColor(Colors::white);
		m_txtCtrlParking->setColor(Colors::black);
		m_txtSeletParking->setColor(Colors::black);
		m_txtMemoryParking->setColor(Colors::black);

		m_CurState = ID_Unknow;

		m_NodeRightRef->SetPopMultiTextState(0);
		m_NodeRightRef->SetParkingHighlight(0);
		m_NodeRemoteCtrlParkingRef->onExitMenu();
		m_NodeLeftRef->onExitMenu();

		m_NodeLeftRef->onEnterMenu(1);
		m_NodeRightRef->SwitchSence(2);
	}
	else if (e.sender == m_btnCtrlParking.get()) {
		m_btnAutoParking->setCheck(false);
		m_btnCtrlParking->setCheck(true);
		m_btnSeletParking->setCheck(false);
		m_btnMemoryParking->setCheck(false);
		m_txtAutoParking->setColor(Colors::black);
		m_txtCtrlParking->setColor(Colors::white);
		m_txtSeletParking->setColor(Colors::black);
		m_txtMemoryParking->setColor(Colors::black);


		m_CurState = ID_RemoteParking;
		m_nCurrentPage = 1;

		m_NodeLeftRef->onExitMenu();

		m_NodeRightRef->SwitchSence(1);
		m_NodeRightRef->SetPopMultiTextState(1);
		m_NodeRightRef->SetParkingHighlight(0);

		m_NodeRemoteCtrlParkingRef->onEnterMenu();

		m_nCurrentPage++;
	}
	else if(e.sender == m_btnSeletParking.get()) {
		m_btnAutoParking->setCheck(false);
		m_btnCtrlParking->setCheck(false);
		m_btnSeletParking->setCheck(true);
		m_btnMemoryParking->setCheck(false);
		m_txtAutoParking->setColor(Colors::black);
		m_txtCtrlParking->setColor(Colors::black);
		m_txtSeletParking->setColor(Colors::white);
		m_txtMemoryParking->setColor(Colors::black);

		m_CurState = ID_SeltParking;
		m_nCurrentPage = 0;

		m_NodeRemoteCtrlParkingRef->onExitMenu();
		m_NodeLeftRef->onExitMenu();

		m_NodeLeftRef->onEnterMenu(0);
		m_NodeRightRef->SwitchSence(1);
		m_NodeRightRef->SetParkingHighlight(0);
		m_NodeRightRef->SetPopMultiTextState(0);
	}
	else if (e.sender == m_btnMemoryParking.get()) {
		MainView::get()->switchView<MemoryParking>();
	}
}

void IntelligentParkingView::onTouch(const TouchEventArgs &e)
{
	if (e.action != TouchActionE::up)
		return;

	if (m_btnAutoParking->isPressed() || \
		m_btnCtrlParking->isPressed() || \
		m_btnSeletParking->isPressed())
		return;

	switch (m_CurState)
	{
	case ID_AutoParking:
		{
		}
		break;
	case ID_RemoteParking:
		{
			if (m_nCurrentPage >= 7) m_nCurrentPage = 1;

			if (m_nCurrentPage == 1 || m_nCurrentPage == 2) {
				
				m_NodeRightRef->SwitchSence(1);
				m_NodeRightRef->SetPopMultiTextState(m_nCurrentPage);
				m_NodeRemoteCtrlParkingRef->onFreshMenu(2);
			}
			else {
				m_NodeRightRef->SwitchSence(0);
				m_NodeRightRef->SetPopMultiTextState(0);
				m_NodeRemoteCtrlParkingRef->onFreshMenu(m_nCurrentPage);
			}

			m_nCurrentPage++;
		}
		break;
	case ID_SeltParking:
		{
		}
		break;
	default:
		break;
	}

}

void IntelligentParkingView::selectParking(int index)
{
	m_NodeRightRef->SetParkingHighlight(index);
}

void IntelligentParkingView::setAutoParking()
{
	m_CurState = ID_AutoParking;
	m_nCurrentPage = 2;

	m_NodeRemoteCtrlParkingRef->onExitMenu();
	m_NodeLeftRef->onExitMenu();

	m_NodeLeftRef->onEnterMenu(1);
	m_NodeRightRef->SwitchSence(2);
	m_NodeRightRef->SetPopMultiTextState(0);

	m_timerAutoParkingPlayer.start(3000);
}

void IntelligentParkingView::onAutoParkingPlayTick(const EventArgs & e)
{
	if (m_nCurrentPage >= 5) {
		m_CurState = ID_Unknow;
		m_nCurrentPage = 2;

		m_NodeLeftRef->onEnterMenu(1);
		m_NodeRightRef->SwitchSence(2);

		m_timerAutoParkingPlayer.stop();
		return;
	}

	m_NodeRightRef->SwitchSence(m_nCurrentPage + 1);
	m_NodeLeftRef->onEnterMenu(m_nCurrentPage);
	m_nCurrentPage++;
}

void IntelligentParkingView::onBtnClick(const EventArgs &e)
{
	if (e.sender == m_BtnBack.get()) {
		MainView::get()->switchView<ManualParkingView>();
	}
}
