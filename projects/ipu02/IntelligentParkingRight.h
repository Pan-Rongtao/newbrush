#pragma once

#include "newbrush/UserControl.h"
#include "newbrush/Node2D.h"
#include "newbrush/Components.h"
#include "newbrush/Font.h"
#include "newbrush/StateManager.h"

namespace nb {
class IntelligentParkingRight;
typedef ref<IntelligentParkingRight> IntelligentParkingRightRef;


class IntelligentParkingRightA3;
typedef ref<IntelligentParkingRightA3> IntelligentParkingRightA3Ref;

class NB_API IntelligentParkingRight : public Node2D
{
public:
	IntelligentParkingRight(float x, float y, float w, float h);
	virtual ~IntelligentParkingRight();

	static IntelligentParkingRightRef createIntelligentParkingRightRef(float x, float y, float w, float h);
public:
	//virtual void onRender() override;

	void SetPopState(int state); // 切换弹窗
	void SetPopMultiTextState(int state); //切换多行文本提醒
	void SetParkingHighlight(int index); //设置车位，1~4，上到下
	
	
	void SwitchSence(int index); //切换界面，0隐藏，1~5；

	void onBtnClickedStartPark(const EventArgs &arg);
	void onBtnClickedContinuePark(const EventArgs &arg);
	void onBtnClickedTest(const EventArgs &arg);

private:

	float m_offsetx;
	float m_offsety;


	ref<Node2D> m_bgroad;

	/***********  查找车位  *******************/
	ref<Node2D> m_car;
	ref<Node2D> m_radar;

	ref<Node2D> m_rightheng1s;
	ref<Node2D> m_rightheng2s;
	ref<Node2D> m_rightheng3s;
	ref<Node2D> m_rightheng4s;

	ref<Node2D> m_rightheng1n;
	ref<Node2D> m_rightheng2n;
	ref<Node2D> m_rightheng3n;
	ref<Node2D> m_rightheng4n;

	ref<Node2D> m_rightshu1n;
	ref<Node2D> m_rightshu2n;

	ref<Node2D> m_rightshu1s;
	ref<Node2D> m_rightshu2s;


	//ref<Button> m_rightheng1btn;
	//ref<Button> m_rightheng2btn;
	//ref<Button> m_rightheng3btn;
	//ref<Button> m_rightheng4btn;

	ref<Button> m_btnStarParking;
	ref<TextBlock> m_btnStarParkingText;

	ref<Node2D> m_nodeStartParking;


	ref<Node2D> m_bgBackUp;

	/***********  顶部提示框  *******************/
	ref<Node2D> m_topTipNode;
	ref<TextBlock> m_topText;
	ref<Node2D> m_topBg;

	/***********  底部提示框  *******************/
	ref<TextBlock> m_bottomText;

	/***********  自动泊车弹窗  *******************/
	ref<Node2D> m_popClose;
	ref<Node2D> m_popCloseBG;
	ref<Node2D> m_popClosePic;
	ref<TextBlock> m_popCloseText;

	ref<Button> m_btnContinueParking;
	ref<TextBlock> m_btnContinueParkingText;
	ref<Node2D> m_nodeContinueParking;
	//ref<StateManager> m_smpopClosePic;


	/***********  遥控泊车流程  *******************/
	ref<Node2D> m_popMultiText0;
	ref<Node2D> m_popMultiText0BG;
	ref<TextBlock> m_titlePopMultiText;
	ref<Node2D>m_num1;
	ref<Node2D>m_num2;
	ref<Node2D>m_num3;
	ref<Node2D>m_num4;
	ref<Node2D>m_num5;
	ref<TextBlock>m_text1;
	ref<TextBlock>m_text2;
	ref<TextBlock>m_text3;
	ref<TextBlock>m_text4;
	ref<TextBlock>m_text5;

	/***********  多行文本警告  ********************/
	ref<Node2D> m_popwarn;
	ref<Node2D> m_popwarnBG;
	ref<TextBlock> m_tiptilewarn;
	ref<TextBlock> m_tiptilewarnContent1;
	ref<TextBlock> m_tiptilewarnContent2;
	ref<TextBlock> m_tiptilewarnContent3;
	ref<TextBlock> m_tiptilewarnContent4;

	int m_btnstate;

	/*     test btn */

	ref<Button> m_btntest;

};




}
