#pragma once

#include "PageBase.h"

using namespace nb;

enum DETECTIONSTATUS
{
	STATUS_INITIAL = 0,
	STATUS_DETECTING,
	STATUS_FAILED,
	STATUS_FINISHED
};

class PageConditionDetection : public PageBase
{
	using PageBase::PageBase;
public:
	PageConditionDetection(const Rect &rc, NBPageID id);
	PageConditionDetection(float x, float y, float w, float h, NBPageID id);
	void onBtnClicked(const EventArgs &arg);
	void updateStatus(DETECTIONSTATUS status);
protected:
	void init();
private:
	DETECTIONSTATUS m_status;
	ref<Node2D> m_rectstatus;
	ref<TextBlock> m_textstatus;

	ref<Node2D> m_resultbg;
	ref<Node2D> m_car;

	ref<Node2D> m_conditions;
	ref<Node2D> m_iconP;
	ref<TextBlock> m_textP;
	ref<Node2D> m_icondoors;
	ref<TextBlock> m_textdoors;
	ref<Node2D> m_iconcharge;
	ref<TextBlock> m_textcharge;
	ref<Node2D> m_iconbelt;
	ref<TextBlock> m_textbelt;
	ref<Node2D> m_iconroute;
	ref<TextBlock> m_textroute;

	ref<Node2D> m_failed;
	ref<TextBlock> m_failedtext;
	ref<Button> m_retry;
	ref<Button> m_changeroute;

	ref<Button> m_start;
	ref<Node2D> m_rectstart;
	ref<TextBlock> m_textstart;

	ref<Node2D> m_popbg;
	ref<TextBlock> m_poptext;

	//Test buttons
	ref<Button> btn_detecting;
	ref<Button> btn_failed;
	ref<Button> btn_finished;
};