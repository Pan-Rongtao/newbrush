#include "IntelligentParkingRight.h"

#include "newbrush/Helper.h"
#include "newbrush/Renderer2D.h"
#include "../Common.h"
#include "IntelligentParkingView.h"

#include <queue>

const static bool testflag = false;

using namespace nb;

IntelligentParkingRightRef IntelligentParkingRight::createIntelligentParkingRightRef(float x, float y, float w, float h)
{
	auto node = createRef<IntelligentParkingRight>(x, y, w, h);
	return node;
}


IntelligentParkingRight::IntelligentParkingRight(float x, float y, float w, float h)
	: Node2D(x, y, w, h)
{
	//检索车位
	//TextureLibrary::addTextureAtlas("memory", RES_DIR"ipu02/memory.png", RES_DIR"ipu02/memory.txt");
	//TextureLibrary::addTextureAtlas("intelligent_day", RES_DIR"ipu02/intelligent_day.png", RES_DIR"ipu02/intelligent_day.txt");
	//TextureLibrary::addTextureAtlas("extra", RES_DIR"ipu02/intelligent_day_extra.png", RES_DIR"ipu02/intelligent_day_extra.txt");
	TextureLibrary::addTextureAtlas("xyh", RES_DIR"ipu02/xyhpic.png", RES_DIR"ipu02/xyhpic.txt");


	m_offsetx = 610.0f;
	m_offsety = 100.0f;

	//TextureLibrary::getFrameFromTextureAtlas("intelligent_day", "icon_topbar_back.png");
	auto bgroad = createRef<Texture2D>(RES_DIR"ipu02/intelligent/day/autopark_pic_bgroad.png");
	//auto bgroad = TextureLibrary::getFrameFromTextureAtlas("intelligent_day", "autopark_pic_bgroad.png");
	m_bgroad = createRef<Node2D>(0.0f, 0.0f, 1310.0f, 880.0f);
	m_bgroad->setBackground(createRef<ImageBrush>(bgroad));
	addChild(m_bgroad);


//	auto radarpic = createRef<Texture2D>(RES_DIR"ipu02/intelligent/day/pic_radar.png");
	auto radarpic = TextureLibrary::getFrameFromTextureAtlas("xyh", "pic_radar.png");
	m_radar = createRef<Node2D>(0.0f, 0.0f, 450, 244);
	m_radar->setBackground(createRef<ImageBrush>(radarpic));
	m_radar->setPosition(Point(1051 - m_offsetx - 10, 283 - m_offsety - 50));
	addChild(m_radar);

	//auto carpic = createRef<Texture2D>(RES_DIR"ipu02/intelligent/day/pic_car03.png");
	auto carpic = TextureLibrary::getFrameFromTextureAtlas("xyh", "pic_car03.png");
	m_car = createRef<Node2D>(0.0f, 0.0f, 212, 191);
	m_car->setBackground(createRef<ImageBrush>(carpic));
	m_car->setPosition(Point(1159 - m_offsetx, 267 - m_offsety));
	addChild(m_car);

	//auto rightheng1n = createRef<Texture2D>(RES_DIR"ipu02/xyh/xyhrightheng1n.png");
	auto rightheng1n = TextureLibrary::getFrameFromTextureAtlas("xyh", "xyhrightheng1n.png");
	m_rightheng1n = createRef<Node2D>(1447 - m_offsetx, 400 - m_offsety, 303, 71);
	m_rightheng1n->setBackground(createRef<ImageBrush>(rightheng1n));
	addChild(m_rightheng1n);

	//auto rightheng2n = createRef<Texture2D>(RES_DIR"ipu02/xyh/xyhrightheng2n.png");
	auto rightheng2n = TextureLibrary::getFrameFromTextureAtlas("xyh", "xyhrightheng2n.png");
	m_rightheng2n = createRef<Node2D>(1464 - m_offsetx, 472 - m_offsety, 346, 90);
	m_rightheng2n->setBackground(createRef<ImageBrush>(rightheng2n));
	addChild(m_rightheng2n);

	//auto rightheng3n = createRef<Texture2D>(RES_DIR"ipu02/xyh/xyhrightheng3n.png");
	auto rightheng3n = TextureLibrary::getFrameFromTextureAtlas("xyh", "xyhrightheng3n.png");
	m_rightheng3n = createRef<Node2D>(1485 - m_offsetx, 564 - m_offsety, 402, 118);
	m_rightheng3n->setBackground(createRef<ImageBrush>(rightheng3n));
	addChild(m_rightheng3n);
	
	//auto rightheng4n = createRef<Texture2D>(RES_DIR"ipu02/xyh/xyhrightheng4n.png");
	auto rightheng4n = TextureLibrary::getFrameFromTextureAtlas("xyh", "xyhrightheng4n.png");
	m_rightheng4n = createRef<Node2D>(1513 - m_offsetx, 684 - m_offsety, 406, 162);
	m_rightheng4n->setBackground(createRef<ImageBrush>(rightheng4n));
	addChild(m_rightheng4n);

	//auto rightheng1s = createRef<Texture2D>(RES_DIR"ipu02/xyh/xyhrightheng1s.png");
	auto rightheng1s = TextureLibrary::getFrameFromTextureAtlas("xyh", "xyhrightheng1s.png");
	m_rightheng1s = createRef<Node2D>(1447 - m_offsetx, 400 - m_offsety, 303, 71);
	m_rightheng1s->setBackground(createRef<ImageBrush>(rightheng1s));
	addChild(m_rightheng1s);

	//auto rightheng2s = createRef<Texture2D>(RES_DIR"ipu02/xyh/xyhrightheng2s.png");
	auto rightheng2s = TextureLibrary::getFrameFromTextureAtlas("xyh", "xyhrightheng2s.png");
	m_rightheng2s = createRef<Node2D>(1464 - m_offsetx, 472 - m_offsety, 346, 90);
	m_rightheng2s->setBackground(createRef<ImageBrush>(rightheng2s));
	addChild(m_rightheng2s);

	//auto rightheng3s = createRef<Texture2D>(RES_DIR"ipu02/xyh/xyhrightheng3s.png");
	auto rightheng3s = TextureLibrary::getFrameFromTextureAtlas("xyh", "xyhrightheng3s.png");
	m_rightheng3s = createRef<Node2D>(1485 - m_offsetx, 564 - m_offsety, 402, 118);
	m_rightheng3s->setBackground(createRef<ImageBrush>(rightheng3s));
	addChild(m_rightheng3s);

	//auto rightheng4s = createRef<Texture2D>(RES_DIR"ipu02/xyh/xyhrightheng4s.png");
	auto rightheng4s = TextureLibrary::getFrameFromTextureAtlas("xyh", "xyhrightheng4s.png");
	m_rightheng4s = createRef<Node2D>(1513 - m_offsetx, 684 - m_offsety, 406, 162);
	m_rightheng4s->setBackground(createRef<ImageBrush>(rightheng4s));
	addChild(m_rightheng4s);


	//auto rightshu2n = createRef<Texture2D>(RES_DIR"ipu02/xyh/xyhrightshu2n.png");
	auto rightshu2n = TextureLibrary::getFrameFromTextureAtlas("xyh", "xyhrightshu2n.png");
	m_rightshu2n = createRef<Node2D>(1485 - m_offsetx, 564 - m_offsety, 285, 285);
	m_rightshu2n->setBackground(createRef<ImageBrush>(rightshu2n));
	addChild(m_rightshu2n);

	//auto rightshu2s = createRef<Texture2D>(RES_DIR"ipu02/xyh/xyhrightshu2s.png");
	auto rightshu2s = TextureLibrary::getFrameFromTextureAtlas("xyh", "xyhrightshu2s.png");
	m_rightshu2s = createRef<Node2D>(1485 - m_offsetx, 564 - m_offsety, 285, 285);
	m_rightshu2s->setBackground(createRef<ImageBrush>(rightshu2s));
	addChild(m_rightshu2s);

	m_rightheng1s->setVisibility(VisibilityE::Hidden);
	m_rightheng2s->setVisibility(VisibilityE::Hidden);
	m_rightheng3s->setVisibility(VisibilityE::Hidden);
	m_rightheng4s->setVisibility(VisibilityE::Hidden);
	m_rightshu2n->setVisibility(VisibilityE::Hidden);
	m_rightshu2s->setVisibility(VisibilityE::Hidden);
	
	m_bottomText = createRef<TextBlock>(u8"提示：保持直线行驶，距车位侧边0.5！1.5m范围内");
	m_bottomText->setPosition(Point(0, 830 - m_offsety));
	m_bottomText->setHorizontalAlignment(HorizontalAlignmentE::Center);
	addChild(m_bottomText);
	m_bottomText->setVisibility(VisibilityE::Hidden);


	//auto btnStarParkingn = createRef<Texture2D>(RES_DIR"ipu02/memory/autopark_btn_62px_nor.png");
	//auto btnStarParkings = createRef<Texture2D>(RES_DIR"ipu02/memory/autopark_btn_62px_sel.png");

	auto btnStarParkingn = TextureLibrary::getFrameFromTextureAtlas("xyh", "autopark_btn_62px_nor.png");
	auto btnStarParkings = TextureLibrary::getFrameFromTextureAtlas("xyh", "autopark_btn_62px_sel.png");

	m_nodeStartParking = createRef<Node2D>(0, 812 - m_offsety, 200, 62);
	m_nodeStartParking->setHorizontalAlignment(HorizontalAlignmentE::Center);

	m_btnStarParking = createRef<Button>(0, 0, 200, 62);
	m_btnStarParking->setBkgndNormal(createRef<ImageBrush>(btnStarParkingn));
	m_btnStarParking->setBkgndCheck(createRef<ImageBrush>(btnStarParkings));
	m_btnStarParking->Click += nbBindEventFunction(IntelligentParkingRight::onBtnClickedStartPark);
	//m_btnStarParking->Click += nbBindEventFunction(PageClaim::onBtnClicked);
	m_nodeStartParking->addChild(m_btnStarParking);

	m_btnStarParking->setCheck(true);

	m_btnStarParkingText = createRef<TextBlock>(u8"开始泊入");
	//m_btnStarParkingText->setHorizontalAlignment(HorizontalAlignmentE::Center);
	//m_btnStarParkingText->setVerticalAlignment(VerticalAlignmentE::Center);
	m_btnStarParkingText->setPosition(Point(40, 17));
	m_btnStarParkingText->setColor(Color(255, 255, 255, 255));
	//m_topText->setPosition(Point((1310 - m_topText->width()) * 0.5, (86 - m_topText->height()) * 0.5));
	m_nodeStartParking->addChild(m_btnStarParkingText);

	addChild(m_nodeStartParking);


	/***********  自动泊车背景  **************************************************************************************/
	//auto bgBackUp = createRef<Texture2D>(RES_DIR"ipu02/xyh/BgBackUp.png");
	auto bgBackUp = TextureLibrary::getFrameFromTextureAtlas("xyh", "BgBackUp.png");
	m_bgBackUp = createRef<Node2D>(0.0f, 0.0f, 1310.0f, 880.0f);
	m_bgBackUp->setBackground(createRef<ImageBrush>(bgBackUp));
	addChild(m_bgBackUp);

	m_bgBackUp->setVisibility(VisibilityE::Hidden);

	/***********  自动泊车弹窗  **************************************************************************************/
	m_topTipNode = createRef<Node2D>(0.0f, 0.0f, 1310, 86);

	//auto bgtop = createRef<Texture2D>(RES_DIR"ipu02/xyh/xyhtipbg.png");
	auto bgtop = TextureLibrary::getFrameFromTextureAtlas("xyh", "xyhtipbg.png");
	m_topBg = createRef<Node2D>(0.0f, 0.0f, 574, 86);
	m_topBg->setBackground(createRef<ImageBrush>(bgtop));
	m_topBg->setHorizontalAlignment(HorizontalAlignmentE::Center);
	m_topBg->setPosition(Point(0, 20));
	//m_topBg->setVerticalAlignment(VerticalAlignmentE::Center);
	m_topTipNode->addChild(m_topBg);

	m_topText = createRef<TextBlock>(u8"搜索车位中，请低速向前行驶");
	m_topText->setPosition(Point(1058 - m_offsetx, 143 - m_offsety));
	m_topTipNode->addChild(m_topText);

	addChild(m_topTipNode);
	/***********  顶部提示框  **************************************************************************************/


	/***********  自动泊车弹窗  **************************************************************************************/
	//auto bgpopClose = createRef<Texture2D>(RES_DIR"ipu02/xyh/xyhpopbg.png");
	auto bgpopClose = TextureLibrary::getFrameFromTextureAtlas("xyh", "xyhpopbg.png");
	m_popClose = createRef<Node2D>(134, 202, 1040, 477);
	m_popClose->setBackground(createRef<ImageBrush>(bgpopClose));

	//auto popClosePic = createRef<Texture2D>(RES_DIR"ipu02/intelligent/day/pic_closedoor.png");
	auto popClosePic = TextureLibrary::getFrameFromTextureAtlas("xyh", "pic_closedoor.png");
	m_popClosePic = createRef<Node2D>(321, 25, popClosePic.sourceSize.x, popClosePic.sourceSize.y);
	m_popClosePic->setBackground(createRef<ImageBrush>(popClosePic));

	m_popCloseText = createRef<TextBlock>(u8"请关上车门后，继续自动泊入");
	//m_popCloseText->setHorizontalAlignment(HorizontalAlignmentE::Center);
	//m_popCloseText->setVerticalAlignment(VerticalAlignmentE::Center);
	m_popCloseText->setPosition(Point(0, 356));

	//auto nodeContinueParkingn = createRef<Texture2D>(RES_DIR"ipu02/memory/autopark_btn_62px_nor.png");
	//auto nodeContinueParkings = createRef<Texture2D>(RES_DIR"ipu02/memory/autopark_btn_62px_sel.png");

	auto nodeContinueParkingn = TextureLibrary::getFrameFromTextureAtlas("xyh", "autopark_btn_62px_nor.png");
	auto nodeContinueParkings = TextureLibrary::getFrameFromTextureAtlas("xyh", "autopark_btn_62px_sel.png");

	m_nodeContinueParking = createRef<Node2D>(0, 355, 200, 62);
	m_nodeContinueParking->setHorizontalAlignment(HorizontalAlignmentE::Center);

	m_btnContinueParking = createRef<Button>(0, 0, 200, 62);
	m_btnContinueParking->setBkgndNormal(createRef<ImageBrush>(nodeContinueParkingn));
	m_btnContinueParking->setBkgndCheck(createRef<ImageBrush>(nodeContinueParkings));
	m_btnContinueParking->Click += nbBindEventFunction(IntelligentParkingRight::onBtnClickedContinuePark);
	m_nodeContinueParking->addChild(m_btnContinueParking);

	m_btnContinueParking->setCheck(true);

	m_btnContinueParkingText = createRef<TextBlock>(u8"继续泊入");
	//m_btnContinueParkingText->setHorizontalAlignment(HorizontalAlignmentE::Center);
	//m_btnContinueParkingText->setVerticalAlignment(VerticalAlignmentE::Center);
	m_btnContinueParkingText->setPosition(Point(40, 17));
	m_btnContinueParkingText->setColor(Color(255, 255, 255, 255));
	//m_topText->setPosition(Point((1310 - m_topText->width()) * 0.5, (86 - m_topText->height()) * 0.5));
	m_nodeContinueParking->addChild(m_btnContinueParkingText);

	//addChild(m_nodeStartParking);

	m_popClose->addChild(m_popClosePic);
	m_popClose->addChild(m_popCloseText);
	m_popClose->addChild(m_nodeContinueParking);

	addChild(m_popClose);
	/***********  自动泊车弹窗  **************************************************************************************/


	//m_popCloseText = createRef<TextBlock>(u8"泊车已完成，请驾驶员重新接管车辆");

	//addChild(m_popClosePic);
	//addChild(m_popCloseText);

	//SetPopState(3);

	/***********  遥控泊车流程  **************************************************************************************/
	m_popMultiText0 = createRef<Node2D>(0, 0, 1310, 880);
	m_popMultiText0BG = createRef<Node2D>(0, 0, 1310, 880);
	m_popMultiText0->setBackground(createRef<ImageBrush>(bgBackUp));
	m_popMultiText0BG->setBackground(createRef<SolidColorBrush>(Color(255, 255, 255, 240)));
	m_popMultiText0->addChild(m_popMultiText0BG);

	//auto num1Pic = createRef<Texture2D>(RES_DIR"ipu02/intelligent/day/number/autopark_pic_number1.png");
	auto num1Pic = TextureLibrary::getFrameFromTextureAtlas("xyh", "autopark_pic_number1.png");
	m_num1 = createRef<Node2D>(451, 332, num1Pic.sourceSize.x, num1Pic.sourceSize.y);
	m_num1->setBackground(createRef<ImageBrush>(num1Pic));
	m_text1 = createRef<TextBlock>(u8"请挂至P档");
	m_text1->setPosition(Point(509, 336));

	//auto num2Pic = createRef<Texture2D>(RES_DIR"ipu02/intelligent/day/number/autopark_pic_number2.png");
	auto num2Pic = TextureLibrary::getFrameFromTextureAtlas("xyh", "autopark_pic_number2.png");
	m_num2 = createRef<Node2D>(451, 392, num2Pic.sourceSize.x, num2Pic.sourceSize.y);
	m_num2->setBackground(createRef<ImageBrush>(num2Pic));
	m_text2 = createRef<TextBlock>(u8"请打开车联助手APP");
	m_text2->setPosition(Point(509, 396));

	//auto num3Pic = createRef<Texture2D>(RES_DIR"ipu02/intelligent/day/number/autopark_pic_number3.png");
	auto num3Pic = TextureLibrary::getFrameFromTextureAtlas("xyh", "autopark_pic_number3.png");
	m_num3 = createRef<Node2D>(451, 452, num3Pic.sourceSize.x, num3Pic.sourceSize.y);
	m_num3->setBackground(createRef<ImageBrush>(num3Pic));
	m_text3 = createRef<TextBlock>(u8"请保持手机蓝牙链接");
	m_text3->setPosition(Point(509, 456));

	//auto num4Pic = createRef<Texture2D>(RES_DIR"ipu02/intelligent/day/number/autopark_pic_number4.png");
	auto num4Pic = TextureLibrary::getFrameFromTextureAtlas("xyh", "autopark_pic_number4.png");
	m_num4 = createRef<Node2D>(451, 512, num4Pic.sourceSize.x, num4Pic.sourceSize.y);
	m_num4->setBackground(createRef<ImageBrush>(num4Pic));
	m_text4 = createRef<TextBlock>(u8"请保证车内无人乘坐");
	m_text4->setPosition(Point(509, 516));

	//auto num5Pic = createRef<Texture2D>(RES_DIR"ipu02/intelligent/day/number/autopark_pic_number5.png");
	auto num5Pic = TextureLibrary::getFrameFromTextureAtlas("xyh", "autopark_pic_number5.png");
	m_num5 = createRef<Node2D>(451, 572, num5Pic.sourceSize.x, num5Pic.sourceSize.y);
	m_num5->setBackground(createRef<ImageBrush>(num5Pic));
	m_text5 = createRef<TextBlock>(u8"请保证车内无人乘坐");
	m_text5->setPosition(Point(509, 576));

	m_titlePopMultiText = createRef<TextBlock>(u8"条件检测中......");
	m_titlePopMultiText->setPosition(Point(540, 220));

	m_popMultiText0->addChild(m_num1);
	m_popMultiText0->addChild(m_num2);
	m_popMultiText0->addChild(m_num3);
	m_popMultiText0->addChild(m_num4);
	m_popMultiText0->addChild(m_num5);
	m_popMultiText0->addChild(m_text1);
	m_popMultiText0->addChild(m_text2);
	m_popMultiText0->addChild(m_text3);
	m_popMultiText0->addChild(m_text4);
	m_popMultiText0->addChild(m_text5);
	m_popMultiText0->addChild(m_titlePopMultiText);

	addChild(m_popMultiText0);
	/***********  遥控泊车流程  **************************************************************************************/
	

	/***********  多行文本警告  **************************************************************************************/
	m_popwarn = createRef<Node2D>(0, 0, 1310, 880);
	m_popwarnBG = createRef<Node2D>(0, 0, 1310, 880);
	m_popwarn->setBackground(createRef<ImageBrush>(bgBackUp));
	m_popwarnBG->setBackground(createRef<SolidColorBrush>(Color(255, 255, 255, 240)));
	m_popwarn->addChild(m_popwarnBG);
	
	m_tiptilewarn = createRef<TextBlock>(u8"温馨提醒：");
	m_tiptilewarn->setPosition(Point(575, 202));
	m_tiptilewarnContent1 = createRef<TextBlock>(u8"用户请确保选择的车位合法合适且安全，");
	m_tiptilewarnContent1->setPosition(Point(381, 259));
	m_tiptilewarnContent2 = createRef<TextBlock>(u8" 泊车过程请时刻注意观察车辆周围环境");
	m_tiptilewarnContent2->setPosition(Point(373, 305));
	m_tiptilewarnContent3 = createRef<TextBlock>(u8"拖动全景中的车位完成定位，");
	m_tiptilewarnContent3->setPosition(Point(459, 391));
	m_tiptilewarnContent4 = createRef<TextBlock>(u8"通过车位角度按钮微调角度");
	m_tiptilewarnContent4->setPosition(Point(459, 437));

	m_popwarn->addChild(m_tiptilewarn);
	m_popwarn->addChild(m_tiptilewarnContent1);
	m_popwarn->addChild(m_tiptilewarnContent2);
	m_popwarn->addChild(m_tiptilewarnContent3);
	m_popwarn->addChild(m_tiptilewarnContent4);
	addChild(m_popwarn);
	/***********  多行文本警告  **************************************************************************************/

	SetPopMultiTextState(0);
	SetPopState(0);
	SetParkingHighlight(0);
	//SwitchSence(3);

	/* test  */
#if testflag
	if (testflag) {
		m_btntest = createRef<Button>(0, 0, 200, 62);
		m_btntest->setBkgndNormal(createRef<ImageBrush>(btnStarParkingn));
		m_btntest->setBkgndCheck(createRef<ImageBrush>(btnStarParkings));
		m_btntest->Click += nbBindEventFunction(IntelligentParkingRight::onBtnClickedTest);
		addChild(m_btntest);
	}
#endif
}

void IntelligentParkingRight::SetParkingHighlight(int index)
{
	if (0 == index) {
		m_rightheng1s->setVisibility(VisibilityE::Hidden);
		m_rightheng2s->setVisibility(VisibilityE::Hidden);
		m_rightheng3s->setVisibility(VisibilityE::Hidden);
		m_rightheng4s->setVisibility(VisibilityE::Hidden);
	}else if (4 == index) {
		m_rightheng1s->setVisibility(VisibilityE::Visible);
		m_rightheng2s->setVisibility(VisibilityE::Hidden);
		m_rightheng3s->setVisibility(VisibilityE::Hidden);
		m_rightheng4s->setVisibility(VisibilityE::Hidden);
	}
	else if (3 == index) {
		m_rightheng1s->setVisibility(VisibilityE::Hidden);
		m_rightheng2s->setVisibility(VisibilityE::Visible);
		m_rightheng3s->setVisibility(VisibilityE::Hidden);
		m_rightheng4s->setVisibility(VisibilityE::Hidden);
	}
	else if (2 == index) {
		m_rightheng1s->setVisibility(VisibilityE::Hidden);
		m_rightheng2s->setVisibility(VisibilityE::Hidden);
		m_rightheng3s->setVisibility(VisibilityE::Visible);
		m_rightheng4s->setVisibility(VisibilityE::Hidden);
	}
	else if (1 == index) {
		m_rightheng1s->setVisibility(VisibilityE::Hidden);
		m_rightheng2s->setVisibility(VisibilityE::Hidden);
		m_rightheng3s->setVisibility(VisibilityE::Hidden);
		m_rightheng4s->setVisibility(VisibilityE::Visible);
	}
}

void IntelligentParkingRight::SetPopState(int state)
{
	std::string picpath;
	std::string content;
	if (0 == state) {
		m_popClose->setVisibility(VisibilityE::Hidden);
	}
	else if (1 == state) {
		m_popClose->setVisibility(VisibilityE::Visible);
		m_nodeContinueParking->setVisibility(VisibilityE::Hidden);
		picpath = "pic_closedoor.png";
		content = u8"请关上车门后，继续自动泊入";
		
		m_popCloseText->setPosition(Point(308, 356));
	}
	else if (2 == state) {
		m_popClose->setVisibility(VisibilityE::Visible);
		m_nodeContinueParking->setVisibility(VisibilityE::Hidden);
		picpath ="pic_steeringwheel.png";
		content = u8"泊车已完成，请驾驶员重新接管车辆";
		
		m_popCloseText->setPosition(Point(263, 356));
	}
	else if (3 == state) {
		m_popClose->setVisibility(VisibilityE::Visible);
		m_nodeContinueParking->setVisibility(VisibilityE::Visible);
		m_btnContinueParkingText->setText(u8"继续泊入");

		picpath = "pic_parkpause.png";
		content = u8"请点击下方按钮继续自动泊车";
	
		m_popCloseText->setPosition(Point(308, 276));
	}
	else if (4 == state) {
		m_popClose->setVisibility(VisibilityE::Visible);
		m_nodeContinueParking->setVisibility(VisibilityE::Visible);
		m_btnContinueParkingText->setText(u8"开始泊入");

		picpath = "pic_parkpause.png";
		content = u8"拖动全景中的车位完成定位，通过车位角度按钮微调角度";

		m_popCloseText->setPosition(Point(109, 276));
	}

	auto popClosePic = TextureLibrary::getFrameFromTextureAtlas("xyh", picpath);
	//auto popClosePic = createRef<Texture2D>(picpath);
	m_popClosePic->setWidth(popClosePic.sourceSize.x);
	m_popClosePic->setHeight(popClosePic.sourceSize.y);
	m_popClosePic->setBackground(createRef<ImageBrush>(popClosePic));

	m_popCloseText->setText(content);
	m_popCloseText->setHorizontalAlignment(HorizontalAlignmentE::Center);
}

void IntelligentParkingRight::SetPopMultiTextState(int state)
{
	if (0 == state) {
		m_popwarn->setVisibility(VisibilityE::Hidden);
		m_popMultiText0->setVisibility(VisibilityE::Hidden);
	}
	else if (1 == state) {
		m_text1->setText(u8"请挂至P档");
		m_text2->setText(u8"请打开车联助手APP");
		m_text3->setText(u8"请保持手机蓝牙链接");
		m_text4->setText(u8"请保证车内无人乘坐");
		m_text5->setText(u8"请保证车内无人乘坐");

		m_text1->setColor(Color(0, 0, 0, 255));
		m_text2->setColor(Color(0, 0, 0, 255));
		m_text3->setColor(Color(0, 0, 0, 255));
		m_text4->setColor(Color(0, 0, 0, 255));
		m_text5->setColor(Color(0, 0, 0, 255));

		m_num5->setVisibility(VisibilityE::Hidden);
		m_text5->setVisibility(VisibilityE::Hidden);
		m_titlePopMultiText->setVisibility(VisibilityE::Hidden);
		m_popwarn->setVisibility(VisibilityE::Hidden);
	}
	else if (2 == state) {
		m_text1->setText(u8"请挂至P档");
		m_text2->setText(u8"请打开车联助手APP");
		m_text3->setText(u8"请保持手机蓝牙链接");
		m_text4->setText(u8"请关闭车门、后备箱、引擎盖");
		m_text5->setText(u8"钥匙不在车内");

		m_text1->setColor(Color(0, 255, 0, 255));
		m_text2->setColor(Color(0, 255, 0, 255));
		m_text3->setColor(Color(255, 0, 0, 255));
		m_text4->setColor(Color(0, 0, 0, 255));
		m_text5->setColor(Color(0, 0, 0, 255));

		m_num5->setVisibility(VisibilityE::Visible);
		m_text5->setVisibility(VisibilityE::Visible);
		m_titlePopMultiText->setVisibility(VisibilityE::Visible);
		m_popwarn->setVisibility(VisibilityE::Hidden);
	}
	else if (3 == state) {
		m_popwarn->setVisibility(VisibilityE::Visible);
		m_popMultiText0->setVisibility(VisibilityE::Hidden);
	}
	if (0 != state) {
		m_popMultiText0->setVisibility(VisibilityE::Visible);
	}
}

void IntelligentParkingRight::SwitchSence(int index)
{
	if (0 == index) {
		setVisibility(VisibilityE::Hidden);
#if testflag
		if (testflag) {
			setVisibility(VisibilityE::Visible);
		}
#endif
	}
	else if (1 == index) {
		m_topTipNode->setVisibility(VisibilityE::Visible);
		m_rightheng1n->setVisibility(VisibilityE::Visible);
		m_rightheng2n->setVisibility(VisibilityE::Visible);
		m_rightheng3n->setVisibility(VisibilityE::Visible);
		m_rightheng4n->setVisibility(VisibilityE::Visible);
		m_bgBackUp->setVisibility(VisibilityE::Hidden);

		m_topBg->setWidth(479);
		m_topBg->setHorizontalAlignment(HorizontalAlignmentE::Center);
		m_topBg->setVerticalAlignment(VerticalAlignmentE::Center);

		m_topText->setText(u8"请点击按钮，开始泊车");
		m_topText->setPosition(Point(1107 - m_offsetx, 143 - m_offsety));

		SetPopState(0);
	}
	else if (2 == index) {
		m_topTipNode->setVisibility(VisibilityE::Visible);
		m_rightheng1n->setVisibility(VisibilityE::Hidden);
		m_rightheng2n->setVisibility(VisibilityE::Hidden);
		m_rightheng3n->setVisibility(VisibilityE::Hidden);
		m_rightheng4n->setVisibility(VisibilityE::Hidden);
		m_bgBackUp->setVisibility(VisibilityE::Hidden);

		m_topBg->setWidth(479);
		m_topBg->setHorizontalAlignment(HorizontalAlignmentE::Center);
		m_topBg->setVerticalAlignment(VerticalAlignmentE::Center);

		m_topText->setText(u8"请点击按钮，开始泊车");
		m_topText->setPosition(Point(1107 - m_offsetx, 143 - m_offsety));

		m_btnStarParking->setVisibility(VisibilityE::Visible);
		m_btnStarParkingText->setVisibility(VisibilityE::Visible);
		
		//SetParkingHighlight(2);
		SetPopState(0);
	}
	else if (3 == index) {
		m_topTipNode->setVisibility(VisibilityE::Visible);
		m_bgBackUp->setVisibility(VisibilityE::Visible);

		m_topBg->setWidth(446);
		m_topBg->setHorizontalAlignment(HorizontalAlignmentE::Center);
		m_topBg->setVerticalAlignment(VerticalAlignmentE::Center);

		m_topText->setText(u8"请松开方向盘和刹车");
		m_topText->setPosition(Point(1122 - m_offsetx, 143 - m_offsety));

		SetPopState(0);
	}
	else if (4 == index) {
		m_topTipNode->setVisibility(VisibilityE::Visible);
		m_bgBackUp->setVisibility(VisibilityE::Visible);
		m_topBg->setWidth(312);
		m_topBg->setHorizontalAlignment(HorizontalAlignmentE::Center);
		m_topBg->setVerticalAlignment(VerticalAlignmentE::Center);

		m_topText->setText(u8"自动泊入中");
		m_topText->setPosition(Point(1184 - m_offsetx, 143 - m_offsety));

		SetPopState(0);
	}
	else if (5 == index) {
		m_topTipNode->setVisibility(VisibilityE::Hidden);
		m_bgBackUp->setVisibility(VisibilityE::Visible);
		SetPopState(2);
	}
	if (0 != index) {
		setVisibility(VisibilityE::Visible);
	}
}


void IntelligentParkingRight::onBtnClickedStartPark(const EventArgs &arg)
{
	printf(" click the start part button;");

	Node2D *pNode = this->getParent();
	if (is<IntelligentParkingView>(pNode)) {
		as<IntelligentParkingView>(pNode)->setAutoParking();

		m_btnStarParking->setVisibility(VisibilityE::Hidden);
		m_btnStarParkingText->setVisibility(VisibilityE::Hidden);
	}
}

void IntelligentParkingRight::onBtnClickedContinuePark(const EventArgs &arg)
{
	printf(" click the continue part button;");
}


void IntelligentParkingRight::onBtnClickedTest(const EventArgs &arg)
{
	/* test */
#if testflag
	if (testflag) {

		SetPopMultiTextState(0);
		SetPopState(0);
		SetParkingHighlight(0);
		SwitchSence(0);
		static int ii = 0;
		ii++;
		if (ii < 10) {
			SetPopMultiTextState(ii % 6);
		}
		else if (ii < 20) { SetPopState(ii % 6); }
		else if (ii < 30) { SetParkingHighlight(ii % 6); }
		else if (ii < 40) { SwitchSence(ii % 6); }
	}
#endif
	printf(" click the test button;");
}

IntelligentParkingRight::~IntelligentParkingRight()
{
}


