#include "IntelligentRemoteCtrlParking.h"

#include "newbrush/Helper.h"
#include "newbrush/Renderer2D.h"
#include "../Common.h"

#include <queue>

using namespace nb;

IntelligentRemoteCtrlParking::~IntelligentRemoteCtrlParking()
{
}

IntelligentRemoteCtrlParking::IntelligentRemoteCtrlParking()
	: Node2D()
{
	m_timerAutoParking.Tick += nbBindEventFunction(IntelligentRemoteCtrlParking::onTick);
}

void IntelligentRemoteCtrlParking::onEnterMenu()
{
	onFreshMenu(2);
	this->setVisibility(VisibilityE::Visible);
}

void IntelligentRemoteCtrlParking::onExitMenu()
{
	clearChildren();
	this->setVisibility(VisibilityE::Hidden);
}

void IntelligentRemoteCtrlParking::onFreshMenu(int id)
{
	m_timerAutoParking.stop();
	clearChildren();

	if (2 == id) {
		auto imgBg = createRef<Texture2D>(RES_DIR"ipu02/RealLeftScene.png");
		auto node = createRef<Node2D>(0, 100, imgBg->width(), imgBg->height());
		node->setBackground(createRef<ImageBrush>(imgBg));
		
		m_BtnParkingRightHor3 = Button::createWithTextureFrameName("extra", "ParkingRightHor_n.png", true, 412, 631);
		m_BtnParkingRightHor3->setBkgndCheck(createRef<ImageBrush>("extra", "ParkingRightHor_s.png"));
		m_BtnParkingRightHor3->setBkgndDisable(createRef<ImageBrush>("extra", "ParkingRightHor_n.png"));
		node->addChild(m_BtnParkingRightHor3);

		auto texFrame = TextureLibrary::getFrameFromTextureAtlas("extra", "autopark_pic_subline_right.png");
		auto nodeSubLineRightRef = createRef<Node2D>(160, 480, texFrame.sourceSize.x, texFrame.sourceSize.y);
		nodeSubLineRightRef->setBackground(createRef<ImageBrush>(texFrame));
		node->addChild(nodeSubLineRightRef);

		texFrame = TextureLibrary::getFrameFromTextureAtlas("extra", "Car.png");
		auto nodeCarRef = createRef<Node2D>(206, 252, texFrame.sourceSize.x, texFrame.sourceSize.y);
		nodeCarRef->setBackground(createRef<ImageBrush>(texFrame));
		node->addChild(nodeCarRef);

		addChild(node);

		m_timerAutoParking.start(500);
	}
	if (3 == id) {
		auto imgBg = createRef<Texture2D>(RES_DIR"ipu02/intelligent/day/autopark_pic.png");
		auto node = createRef<Node2D>(0, 0, imgBg->width(), imgBg->height());
		node->setBackground(createRef<ImageBrush>(imgBg));

		auto txt = createRef<TextBlock>(u8"遥控泊车进行中......");
		txt->setPosition(Point(702, 131));
		node->addChild(txt);

		addChild(node);
	}
	else if (4 == id) {
		auto node = createRef<Node2D>();
		node->setBackground(createRef<SolidColorBrush>(Color(238, 240, 245)));

		auto texFrame = TextureLibrary::getFrameFromTextureAtlas("intelligent_day", "autopark_pic_pause.png");
		auto nodeImage = createRef<Node2D>(864, 376, texFrame.sourceSize.x, texFrame.sourceSize.y);
		nodeImage->setBackground(createRef<ImageBrush>(texFrame));

		auto txt = createRef<TextBlock>(u8"遥控泊车暂停");
		txt->setPosition(Point(893, 626));

		node->addChild(nodeImage);
		node->addChild(txt);
		addChild(node);
	}
	else if (5 == id) {
		auto node = createRef<Node2D>();
		node->setBackground(createRef<SolidColorBrush>(Color(238, 240, 245)));

		auto texFrame = TextureLibrary::getFrameFromTextureAtlas("intelligent_day", "autopark_pic_alert.png");
		auto nodeImage = createRef<Node2D>(864, 376, texFrame.sourceSize.x, texFrame.sourceSize.y);
		nodeImage->setBackground(createRef<ImageBrush>(texFrame));

		auto txt = createRef<TextBlock>(u8"遥控泊车已终止");
		txt->setPosition(Point(893, 626));

		node->addChild(nodeImage);
		node->addChild(txt);
		addChild(node);
	}
	else if (6 == id) {
		auto node = createRef<Node2D>();
		node->setBackground(createRef<SolidColorBrush>(Color(238, 240, 245)));

		auto texFrame = TextureLibrary::getFrameFromTextureAtlas("intelligent_day", "autopark_pic_compete.png");
		auto nodeImage = createRef<Node2D>(864, 376, texFrame.sourceSize.x, texFrame.sourceSize.y);
		nodeImage->setBackground(createRef<ImageBrush>(texFrame));

		auto txt = createRef<TextBlock>(u8"遥控泊车完成");
		txt->setPosition(Point(893, 626));

		node->addChild(nodeImage);
		node->addChild(txt);
		addChild(node);
	}
}

void IntelligentRemoteCtrlParking::onTick(const EventArgs & e)
{
	if (e.sender == &m_timerAutoParking) {
		bool check = m_BtnParkingRightHor3->isChecked();
		m_BtnParkingRightHor3->setCheck(!check);
	}
}




