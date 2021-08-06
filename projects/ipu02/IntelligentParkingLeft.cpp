#include "IntelligentParkingLeft.h"

#include "newbrush/Helper.h"
#include "newbrush/Renderer2D.h"
#include "../Common.h"
#include "IntelligentParkingView.h"

#include <queue>

using namespace nb;

IntelligentParkingLeftRef IntelligentParkingLeft::createIntelligentParkingLeftRef(float x, float y, float w, float h)
{
	auto node = createRef<IntelligentParkingLeft>(x, y, w, h);
	return node;
}


IntelligentParkingLeft::IntelligentParkingLeft(float x, float y, float w, float h)
	: Node2D(x, y, w, h)
{
	m_timerAutoParking.Tick += nbBindEventFunction(IntelligentParkingLeft::onTick);
	//initVirtualParking();
	//initRealParking();

	auto texFrame = TextureLibrary::getFrameFromTextureAtlas("extra", "autopark_pic_subline_left.png");
	m_NodeSubLineLeftRef = createRef<Node2D>(0, 480, texFrame.sourceSize.x, texFrame.sourceSize.y);
	m_NodeSubLineLeftRef->setBackground(createRef<ImageBrush>(texFrame));
	//addChild(m_NodeSubLineLeftRef);

	m_AnimationMgr.SetEasingType(EasingCurve::InSine);
	m_AnimationMgr.Tick += nbBindEventFunction(IntelligentParkingLeft::onAnimationUpdate);
}

IntelligentParkingLeft::~IntelligentParkingLeft()
{
}

void IntelligentParkingLeft::onEnterMenu(int id)
{
	auto imgBg = createRef<Texture2D>(RES_DIR"ipu02/RealLeftScene.png");
	setBackground(createRef<ImageBrush>(imgBg));

	m_timerAutoParking.stop();
	m_AnimationMgr.Stop();
	this->clearChildren();

	if (0 == id) {
		m_BtnParkingRightHor0 = Button::createWithTextureFrameName("extra", "ParkingRightHor_n.png", true, 412, 91);
		m_BtnParkingRightHor0->setBkgndPress(createRef<ImageBrush>("extra", "ParkingRightHor_s.png"));
		m_BtnParkingRightHor0->setBkgndCheck(createRef<ImageBrush>("extra", "ParkingRightHor_s.png"));
		m_BtnParkingRightHor0->Click += nbBindEventFunction(IntelligentParkingLeft::onSwitchBtnParkingClick);
		addChild(m_BtnParkingRightHor0);

		m_BtnParkingRightHor1 = Button::createWithTextureFrameName("extra", "ParkingRightHor_n.png", true, 412, 271);
		m_BtnParkingRightHor1->setBkgndPress(createRef<ImageBrush>("extra", "ParkingRightHor_s.png"));
		m_BtnParkingRightHor1->setBkgndCheck(createRef<ImageBrush>("extra", "ParkingRightHor_s.png"));
		m_BtnParkingRightHor1->Click += nbBindEventFunction(IntelligentParkingLeft::onSwitchBtnParkingClick);
		addChild(m_BtnParkingRightHor1);

		m_BtnParkingRightHor2 = Button::createWithTextureFrameName("extra", "ParkingRightHor_n.png", true, 412, 451);
		m_BtnParkingRightHor2->setBkgndPress(createRef<ImageBrush>("extra", "ParkingRightHor_s.png"));
		m_BtnParkingRightHor2->setBkgndCheck(createRef<ImageBrush>("extra", "ParkingRightHor_s.png"));
		m_BtnParkingRightHor2->Click += nbBindEventFunction(IntelligentParkingLeft::onSwitchBtnParkingClick);
		addChild(m_BtnParkingRightHor2);

		m_BtnParkingRightHor3 = Button::createWithTextureFrameName("extra", "ParkingRightHor_n.png", true, 412, 631);
		m_BtnParkingRightHor3->setBkgndPress(createRef<ImageBrush>("extra", "ParkingRightHor_s.png"));
		m_BtnParkingRightHor3->setBkgndCheck(createRef<ImageBrush>("extra", "ParkingRightHor_s.png"));
		m_BtnParkingRightHor3->Click += nbBindEventFunction(IntelligentParkingLeft::onSwitchBtnParkingClick);
		addChild(m_BtnParkingRightHor3);

		//m_BtnParkingRightVer0 = Button::createWithTextureFrameName("extra", "ParkingRightVer_n.png", true, 429, 129);
		//m_BtnParkingRightVer0->setBkgndPress(createRef<ImageBrush>("extra", "ParkingRightVer_s.png"));
		//addChild(m_BtnParkingRightVer0);

		//m_BtnParkingRightVer1 = Button::createWithTextureFrameName("extra", "ParkingRightVer_n.png", true, 429, 450);
		//m_BtnParkingRightVer1->setBkgndPress(createRef<ImageBrush>("extra", "ParkingRightVer_s.png"));
		//addChild(m_BtnParkingRightVer1);

		auto texFrame = TextureLibrary::getFrameFromTextureAtlas("extra", "Car.png");
		m_NodeCarRef = createRef<Node2D>(206, 252, texFrame.sourceSize.x, texFrame.sourceSize.y);
		m_NodeCarRef->setBackground(createRef<ImageBrush>(texFrame));
		addChild(m_NodeCarRef);
	}
	else if (1 == id) {
		m_BtnParkingRightHor3 = Button::createWithTextureFrameName("extra", "ParkingRightHor_n.png", true, 412, 631);
		m_BtnParkingRightHor3->setBkgndCheck(createRef<ImageBrush>("extra", "ParkingRightHor_s.png"));
		m_BtnParkingRightHor3->setBkgndDisable(createRef<ImageBrush>("extra", "ParkingRightHor_n.png"));
		//m_BtnParkingRightHor3->setEnable(false);
		addChild(m_BtnParkingRightHor3);

		auto texFrame = TextureLibrary::getFrameFromTextureAtlas("extra", "Car.png");
		m_NodeCarRef = createRef<Node2D>(206, 252, texFrame.sourceSize.x, texFrame.sourceSize.y);
		m_NodeCarRef->setBackground(createRef<ImageBrush>(texFrame));
		addChild(m_NodeCarRef);
	}
	else if (2 == id) {
		m_BtnParkingRightHor3 = Button::createWithTextureFrameName("extra", "ParkingRightHor_n.png", true, 412, 631);
		m_BtnParkingRightHor3->setBkgndCheck(createRef<ImageBrush>("extra", "ParkingRightHor_s.png"));
		m_BtnParkingRightHor3->setBkgndDisable(createRef<ImageBrush>("extra", "ParkingRightHor_n.png"));
		addChild(m_BtnParkingRightHor3);

		auto texFrame = TextureLibrary::getFrameFromTextureAtlas("extra", "autopark_pic_subline_right.png");
		m_NodeSubLineRightRef = createRef<Node2D>(160, 480, texFrame.sourceSize.x, texFrame.sourceSize.y);
		m_NodeSubLineRightRef->setBackground(createRef<ImageBrush>(texFrame));
		addChild(m_NodeSubLineRightRef);

		texFrame = TextureLibrary::getFrameFromTextureAtlas("extra", "Car.png");
		m_NodeCarRef = createRef<Node2D>(206, 252, texFrame.sourceSize.x, texFrame.sourceSize.y);
		m_NodeCarRef->setBackground(createRef<ImageBrush>(texFrame));
		addChild(m_NodeCarRef);

		m_timerAutoParking.start(500);
	}
	else if (3 == id) {
		m_BtnParkingRightHor3 = Button::createWithTextureFrameName("extra", "ParkingRightHor_n.png", true, 412, 631);
		m_BtnParkingRightHor3->setBkgndCheck(createRef<ImageBrush>("extra", "ParkingRightHor_s.png"));
		m_BtnParkingRightHor3->setBkgndDisable(createRef<ImageBrush>("extra", "ParkingRightHor_n.png"));
		addChild(m_BtnParkingRightHor3);

		auto texFrame = TextureLibrary::getFrameFromTextureAtlas("extra", "autopark_pic_subline_right.png");
		m_NodeSubLineRightRef = createRef<Node2D>(160, 480, texFrame.sourceSize.x, texFrame.sourceSize.y);
		m_NodeSubLineRightRef->setBackground(createRef<ImageBrush>(texFrame));
		addChild(m_NodeSubLineRightRef);

		texFrame = TextureLibrary::getFrameFromTextureAtlas("intelligent_day", "car_f.png");
		auto nodeCarfRef = createRef<Node2D>(206, 252, texFrame.sourceSize.x, texFrame.sourceSize.y);
		nodeCarfRef->setBackground(createRef<ImageBrush>(texFrame));
		nodeCarfRef->setTransform(createRef<RotateTransform2D>(-30.0f, nodeCarfRef->width() / 2, nodeCarfRef->height() / 2));
		nodeCarfRef->setPosition(Point(206, 300));
		addChild(nodeCarfRef);

		texFrame = TextureLibrary::getFrameFromTextureAtlas("extra", "Car.png");
		m_NodeCarRef = createRef<Node2D>(206, 252, texFrame.sourceSize.x, texFrame.sourceSize.y);
		m_NodeCarRef->setBackground(createRef<ImageBrush>(texFrame));
		addChild(m_NodeCarRef);

		m_AniRotate.SetAnimationData(252, 450);
		m_AniMove.SetAnimationData(0, -60);
		m_AnimationMgr.Start(2000);
		m_timerAutoParking.start(500);
	}
	else if (4 == id) {
		auto imgBg = createRef<Texture2D>(RES_DIR"ipu02/intelligent/day/bg_b.png");
		setBackground(createRef<ImageBrush>(imgBg));

		auto texFrame = TextureLibrary::getFrameFromTextureAtlas("extra", "Parking.png");
		m_NodeParkingCenterRef = createRef<Node2D>(193, 228, texFrame.sourceSize.x, texFrame.sourceSize.y);
		m_NodeParkingCenterRef->setBackground(createRef<ImageBrush>(texFrame));
		addChild(m_NodeParkingCenterRef);

		texFrame = TextureLibrary::getFrameFromTextureAtlas("extra", "ParkingLeft.png");
		m_NodeParkingLeftRef = createRef<Node2D>(0, 228, texFrame.sourceSize.x, texFrame.sourceSize.y);
		m_NodeParkingLeftRef->setBackground(createRef<ImageBrush>(texFrame));
		addChild(m_NodeParkingLeftRef);

		texFrame = TextureLibrary::getFrameFromTextureAtlas("extra", "ParkingRight.png");
		m_NodeParkingRightRef = createRef<Node2D>(430, 228, texFrame.sourceSize.x, texFrame.sourceSize.y);
		m_NodeParkingRightRef->setBackground(createRef<ImageBrush>(texFrame));
		addChild(m_NodeParkingRightRef);

		texFrame = TextureLibrary::getFrameFromTextureAtlas("extra", "Car.png");
		m_NodeCarRef = createRef<Node2D>(206, 252, texFrame.sourceSize.x, texFrame.sourceSize.y);
		m_NodeCarRef->setBackground(createRef<ImageBrush>(texFrame));
		addChild(m_NodeCarRef);
	}

	this->setVisibility(VisibilityE::Visible);
}

void IntelligentParkingLeft::onExitMenu()
{
	this->setVisibility(VisibilityE::Hidden);
	clearChildren();
}

void IntelligentParkingLeft::onSwitchBtnParkingClick(const EventArgs &e)
{
	if (e.sender == m_BtnParkingRightHor0.get()) {
		m_BtnParkingRightHor0->setCheck(true);
		m_BtnParkingRightHor1->setCheck(false);
		m_BtnParkingRightHor2->setCheck(false);
		m_BtnParkingRightHor3->setCheck(false);

		Node2D *pNode = this->getParent();
		if (is<IntelligentParkingView>(pNode)) {
			as<IntelligentParkingView>(pNode)->selectParking(4);
		}
	}
	else if (e.sender == m_BtnParkingRightHor1.get()) {
		m_BtnParkingRightHor0->setCheck(false);
		m_BtnParkingRightHor1->setCheck(true);
		m_BtnParkingRightHor2->setCheck(false);
		m_BtnParkingRightHor3->setCheck(false);

		Node2D *pNode = this->getParent();
		if (is<IntelligentParkingView>(pNode)) {
			as<IntelligentParkingView>(pNode)->selectParking(3);
		}
	}
	else if (e.sender == m_BtnParkingRightHor2.get()) {
		m_BtnParkingRightHor0->setCheck(false);
		m_BtnParkingRightHor1->setCheck(false);
		m_BtnParkingRightHor2->setCheck(true);
		m_BtnParkingRightHor3->setCheck(false);

		Node2D *pNode = this->getParent();
		if (is<IntelligentParkingView>(pNode)) {
			as<IntelligentParkingView>(pNode)->selectParking(2);
		}
	}
	else if (e.sender == m_BtnParkingRightHor3.get()) {
		m_BtnParkingRightHor0->setCheck(false);
		m_BtnParkingRightHor1->setCheck(false);
		m_BtnParkingRightHor2->setCheck(false);
		m_BtnParkingRightHor3->setCheck(true);

		Node2D *pNode = this->getParent();
		if (is<IntelligentParkingView>(pNode)) {
			as<IntelligentParkingView>(pNode)->selectParking(1);
		}
	}
}

void IntelligentParkingLeft::onTick(const EventArgs & e)
{
	if (e.sender == &m_timerAutoParking) {
		bool check = m_BtnParkingRightHor3->isChecked();
		m_BtnParkingRightHor3->setCheck(!check);
	}
}

void IntelligentParkingLeft::onAnimationUpdate(const AnimationArgs & e)
{
	if (e.bStop)
		return;

	float fValue = m_AniMove.Interpolate(e.fPercent);
	m_NodeCarRef->setTransform(createRef<RotateTransform2D>(fValue, m_NodeCarRef->width() / 2, m_NodeCarRef->height() / 2));

	fValue = m_AniRotate.Interpolate(e.fPercent);
	m_NodeCarRef->setPosition(Point(206, fValue));
}

void IntelligentParkingLeft::initVirtualParking()
{
	auto imgBg = createRef<Texture2D>(RES_DIR"ipu02/intelligent/day/bg_b.png");
	setBackground(createRef<ImageBrush>(imgBg));

	auto texFrame = TextureLibrary::getFrameFromTextureAtlas("extra", "Parking.png");
	m_NodeParkingCenterRef = createRef<Node2D>(193, 228, texFrame.sourceSize.x, texFrame.sourceSize.y);
	m_NodeParkingCenterRef->setBackground(createRef<ImageBrush>(texFrame));
	addChild(m_NodeParkingCenterRef);

	texFrame = TextureLibrary::getFrameFromTextureAtlas("extra", "ParkingTopLeft.png");
	m_NodeParkingTopLeftRef = createRef<Node2D>(0, 0, texFrame.sourceSize.x, texFrame.sourceSize.y);
	m_NodeParkingTopLeftRef->setBackground(createRef<ImageBrush>(texFrame));
	addChild(m_NodeParkingTopLeftRef);

	texFrame = TextureLibrary::getFrameFromTextureAtlas("extra", "ParkingTop.png");
	m_NodeParkingTopRef = createRef<Node2D>(191, 0, texFrame.sourceSize.x, texFrame.sourceSize.y);
	m_NodeParkingTopRef->setBackground(createRef<ImageBrush>(texFrame));
	addChild(m_NodeParkingTopRef);

	texFrame = TextureLibrary::getFrameFromTextureAtlas("extra", "ParkingLeft.png");
	m_NodeParkingLeftRef = createRef<Node2D>(0, 228, texFrame.sourceSize.x, texFrame.sourceSize.y);
	m_NodeParkingLeftRef->setBackground(createRef<ImageBrush>(texFrame));
	addChild(m_NodeParkingLeftRef);

	texFrame = TextureLibrary::getFrameFromTextureAtlas("extra", "ParkingRight.png");
	m_NodeParkingRightRef = createRef<Node2D>(430, 228, texFrame.sourceSize.x, texFrame.sourceSize.y);
	m_NodeParkingRightRef->setBackground(createRef<ImageBrush>(texFrame));
	addChild(m_NodeParkingRightRef);

	texFrame = TextureLibrary::getFrameFromTextureAtlas("extra", "ParkingBottomLeft.png");
	m_NodeParkingBottomLeftRef = createRef<Node2D>(0, 670, texFrame.sourceSize.x, texFrame.sourceSize.y);
	m_NodeParkingBottomLeftRef->setBackground(createRef<ImageBrush>(texFrame));
	addChild(m_NodeParkingBottomLeftRef);

	texFrame = TextureLibrary::getFrameFromTextureAtlas("extra", "ParkingBottom.png");
	m_NodeParkingBottomRef = createRef<Node2D>(191, 670, texFrame.sourceSize.x, texFrame.sourceSize.y);
	m_NodeParkingBottomRef->setBackground(createRef<ImageBrush>(texFrame));
	addChild(m_NodeParkingBottomRef);
}

void IntelligentParkingLeft::initRealParking()
{
	auto imgBg = createRef<Texture2D>(RES_DIR"ipu02/RealLeftScene.png");
	setBackground(createRef<ImageBrush>(imgBg));

	m_BtnParkingRightHor0 = Button::createWithTextureFrameName("extra", "ParkingRightHor_n.png", true, 412, 91);
	m_BtnParkingRightHor0->setBkgndPress(createRef<ImageBrush>("extra", "ParkingRightHor_s.png"));
	addChild(m_BtnParkingRightHor0);

	m_BtnParkingRightHor1 = Button::createWithTextureFrameName("extra", "ParkingRightHor_n.png", true, 412, 271);
	m_BtnParkingRightHor1->setBkgndPress(createRef<ImageBrush>("extra", "ParkingRightHor_s.png"));
	addChild(m_BtnParkingRightHor1);

	m_BtnParkingRightHor2 = Button::createWithTextureFrameName("extra", "ParkingRightHor_n.png", true, 412, 451);
	m_BtnParkingRightHor2->setBkgndPress(createRef<ImageBrush>("extra", "ParkingRightHor_s.png"));
	addChild(m_BtnParkingRightHor2);

	m_BtnParkingRightHor3 = Button::createWithTextureFrameName("extra", "ParkingRightHor_n.png", true, 412, 631);
	m_BtnParkingRightHor3->setBkgndPress(createRef<ImageBrush>("extra", "ParkingRightHor_s.png"));
	addChild(m_BtnParkingRightHor3);

	m_BtnParkingRightVer0 = Button::createWithTextureFrameName("extra", "ParkingRightVer_n.png", true, 429, 129);
	m_BtnParkingRightVer0->setBkgndPress(createRef<ImageBrush>("extra", "ParkingRightVer_s.png"));
	addChild(m_BtnParkingRightVer0);

	m_BtnParkingRightVer1 = Button::createWithTextureFrameName("extra", "ParkingRightVer_n.png", true, 429, 450);
	m_BtnParkingRightVer1->setBkgndPress(createRef<ImageBrush>("extra", "ParkingRightVer_s.png"));
	addChild(m_BtnParkingRightVer1);

	m_BtnParkingRightBottomVer = Button::createWithTextureFrameName("extra", "ParkingRightBottomVer_n.png", true, 412, 656);
	m_BtnParkingRightBottomVer->setBkgndPress(createRef<ImageBrush>("extra", "ParkingRightBottomVer_s.png"));
	addChild(m_BtnParkingRightBottomVer);

	m_BtnParkingLeftHor0 = Button::createWithTextureFrameName("extra", "ParkingLeftHor_n.png", true, 0, 91);
	m_BtnParkingLeftHor0->setBkgndPress(createRef<ImageBrush>("extra", "ParkingLeftHor_s.png"));
	addChild(m_BtnParkingLeftHor0);

	m_BtnParkingLeftHor1 = Button::createWithTextureFrameName("extra", "ParkingLeftHor_n.png", true, 0, 271);
	m_BtnParkingLeftHor1->setBkgndPress(createRef<ImageBrush>("extra", "ParkingLeftHor_s.png"));
	addChild(m_BtnParkingLeftHor1);

	m_BtnParkingLeftHor2 = Button::createWithTextureFrameName("extra", "ParkingLeftHor_n.png", true, 0, 451);
	m_BtnParkingLeftHor2->setBkgndPress(createRef<ImageBrush>("extra", "ParkingLeftHor_s.png"));
	addChild(m_BtnParkingLeftHor2);

	m_BtnParkingLeftHor3 = Button::createWithTextureFrameName("extra", "ParkingLeftHor_n.png", true, 0, 631);
	m_BtnParkingLeftHor3->setBkgndPress(createRef<ImageBrush>("extra", "ParkingLeftHor_s.png"));
	addChild(m_BtnParkingLeftHor3);

	m_BtnParkingLeftVer0 = Button::createWithTextureFrameName("extra", "ParkingRightVer_n.png", true, 10, 129);
	m_BtnParkingLeftVer0->setBkgndPress(createRef<ImageBrush>("extra", "ParkingRightVer_s.png"));
	addChild(m_BtnParkingLeftVer0);

	m_BtnParkingLeftVer1 = Button::createWithTextureFrameName("extra", "ParkingRightVer_n.png", true, 10, 450);
	m_BtnParkingLeftVer1->setBkgndPress(createRef<ImageBrush>("extra", "ParkingRightVer_s.png"));
	addChild(m_BtnParkingLeftVer1);

	m_BtnParkingLeftBottomVer = Button::createWithTextureFrameName("extra", "ParkingRightBottomVer_n.png", true, 10, 656);
	m_BtnParkingLeftBottomVer->setBkgndPress(createRef<ImageBrush>("extra", "ParkingRightBottomVer_s.png"));
	addChild(m_BtnParkingLeftBottomVer);

}


