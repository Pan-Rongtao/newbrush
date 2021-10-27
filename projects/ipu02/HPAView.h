#pragma once
#include "../Common.h"

enum class HPAScene
{
	Scene_None,
	Scene_Hello,
	Scene_Tutorial,
	Scene_Main,
	Scene_Ruku,
	Scene_Chuku,
	Scene_Parking,
	Scene_Edit,
};

enum class PathType
{
	None,
	Ruku,
	Chuku,
};

enum class ParkingSlotType
{
	None,
	Settled,
	Temp,
};

enum class CardType
{
	Ready,
	Saving,
	Learning,
	Delete,
	Create,
};

struct Index
{
	int pageIndex;
	int cardIndex;
};

class HelloScene;
class TutorialScene;
class MainScene;
class RukuChukuScene;
class ParkingScene;
class EditCardScene;
class HPAView : public Node2D
{
public:
	HPAView();
	~HPAView();

	void switchScene(HPAScene scene);

private:
	void onLanguageChanged(const int & lan);

	ref<HelloScene> m_helloScene;
	ref<TutorialScene> m_tutoialScene;
	ref<MainScene> m_mainScene;
	ref<RukuChukuScene> m_rukuChukuScene;
	ref<ParkingScene> m_parkingScene;
	ref<EditCardScene> m_editScene;
	HPAScene m_curScene;
	int m_languageEventHandle;
	int m_exitEventHandle;
	int m_switchModeEventHandle;
};

class HelloScene : public Node2D
{
public:
	HelloScene();
	void setLanguage(int lan);

	Event<EventArgs> Start;

private:
	ref<Node2D> m_img;
	ref<Button> m_btnAgree;
	ref<Button> m_btnStart;
};

class TutorialScene : public Node2D
{
public:
	TutorialScene();
	void setLanguage(int lan);

	Event<EventArgs> Start;

private:
	std::string getTitle(int page) const;

	ref<Button> m_btnSkip;
	ref<Button> m_btnStart;
	ref<TextBlock> m_txtTitle;
	ref<DotListCtrl> m_dotListCtrl;
	std::array<ref<TextBlock>, 5> m_txts;
	ref<PageCtrl> m_pageCtrl;
};

class ProgressMaterial : public Material
{
public:
	ProgressMaterial(ref<Texture2D> tex1, ref<Texture2D> tex2);

	virtual void uploadUniform(ref<Camera> camera) override;

	ref<Texture2D> texture1;
	ref<Texture2D> texture2;
	ref<Node2D> node;
	float progress;
};

class MainScene;
class Card : public Node2D
{
public:
	Card(MainScene *mainScene, PathType pathType, ParkingSlotType psType, const std::string &name);

	void setCardType(CardType mode);
	void setIndex(const Index &index);
			
private:
	void updatePathBrief();

	ref<Node2D> m_img;
	ref<TextBlock> m_txtPathIndex;
	ref<Button> m_btnEdit;
	ref<TextBlock> m_txtPathName;
	ref<TextBlock> m_txtPathBrief;
	ref<Button> m_btnStart;
	ref<Brush> m_progressBrush;

	ref<TextBlock> m_txtTip;

	ref<Node2D> m_bgDel;
	ref<TextBlock> m_txtLearnFail;
	ref<TextBlock> m_txtDelTip;
	ref<Node2D> m_iconDel;

	ref<TextBlock> m_txtNewTitle;
	ref<Button> m_btnRuku;
	ref<Button> m_btnChuku;

	Index m_index;
	CardType m_mode;
	PathType m_pathType;
	ParkingSlotType m_psType;
	std::string m_name;

	Timeline m_tlProgress;

	MainScene *m_mainScene;
};

class MainScene : public Node2D
{
public:
	MainScene();
	void setLanguage(int lan);

	void addCard(CardType mode, PathType pathType, ParkingSlotType psType, const std::string &title);
	void removeCard(const Index &index);

	Event<EventArgs> ToTutorialScene;
	struct ToParkingSceneEventArgs { PathType pathType; std::string name; };
	Event<ToParkingSceneEventArgs> ToParkingScene;
	Event<EventArgs> ToRukuScene;
	Event<EventArgs> ToChukuScene;
	struct ToEditCardSceneEventArgs { Index index; ParkingSlotType psType; std::string name; };
	Event<ToEditCardSceneEventArgs> ToEditCardScene;

private:
	int getCardCount() const;
	int getActualCardCount() const;

	ref<TextBlock> m_txtTop;
	ref<TextBlock> m_txtPathChoose;
	ref<Button> m_btnToTutorial;
	ref<PageCtrl> m_pageCtrl;
	ref<DotListCtrl> m_dotListCtrl;
	ref<Card> m_createCard;
};

class RukuChukuScene : public Node2D
{
public:
	enum class Step
	{
		StopToSetOrign,
		SettingOrign,
		SetOrignFailWithDoorOpen,
		SetOrignSuccess,

		StopToSetEnd,
		SettingEnd,
		SetEndSuccess,

		SavingPath,
	};

	RukuChukuScene();

	void setPathType(PathType pathType);
	void gotoStep(Step step);

	Event<EventArgs> BackToMain;
	struct SavePathEventArgs { PathType pathType; ParkingSlotType psType; std::string name; };
	Event<SavePathEventArgs> SavePath;
	Event<EventArgs> Delete;

private:
	ref<Node2D> m_left;
	ref<Button> m_btnBackToMain;
	ref<TextBlock> m_txtTitle;
	std::array<ref<Node2D>, 3> m_icons;
	ref<TextBlock> m_txtTip;
	ref<Node2D> m_iconStop;
	ref<Button> m_btnSetBegOrEnd;
	ref<Node2D> m_iconLoading;

	ref<Node2D> m_editBg;
	ref<TextBlock> m_txtPathName;
	ref<Button> m_btnDel;
	std::array<ref<Button>, 3> m_btnCans;
//	ref<Button> m_btnCandidateHome0;
//	ref<Button> m_btnCandidateOffice;
//	ref<Button> m_btnCandidateHome1;
	ref<TextBlock> m_txtSlotType;
	ref<Button> m_btnSlotSettled;
	ref<Button> m_btnSlotTemp;
	ref<Button> m_btnSavePath;
	ref<Button> m_btnDelPath;

	ref<Node2D> m_tip;
	ref<TextBlock> m_txtTipTitle;
	ref<TextBlock> m_txtTipContent;
	ref<Button> m_btnRetry;
	ref<Button> m_btnExit;
	ref<Node2D> m_rukuImg;
	bool m_bRetried;
	PathType m_pathType;

	ref<Node2D> m_right;
	ref<Image> m_bigImg;
	ref<Button> m_btnCloseBigImg;

	Step m_curStep;

	Timer m_timerToNextStep;
	FloatAnimation m_aniSettingOrigin;
};

class ParkingScene : public Node2D
{
public:
	enum ItemMode
	{
		Checking,
		Warning,
		Ready,
	};

	enum class ParkingStep
	{
		Parking,
		Pause,
		Resume,
		Done,
	};

	ParkingScene();

	void setPathType(PathType pathType);
	void setName(const std::string &name);

	void start();
	void stop();

	void startPark(bool b);

	void setParkStep(ParkingStep step);

private:
	class Item : public Node2D
	{
	public:
		Item();

		void setText(const std::string &txt);
		void setMode(ItemMode mode);

	private:
		ref<Node2D> m_icon;
		ref<TextBlock> m_txt;
		FloatAnimation m_aniChecking;
	};

	void onTick(const EventArgs &e);

	ref<Node2D> m_checkParent;
	ref<Node2D> m_carBg;
	ref<Node2D> m_car;
	ref<TextBlock> m_title;
	std::array<ref<Item>, 5> m_items;
	ref<Button> m_btnStartPark;

	FloatAnimation m_aniOpacity;
	Timer m_timer;
	Timer m_timerParkStep;
	int m_tick;
	int m_tickParkStep;

	ref<Node2D> m_left;
	ref<TextBlock> m_txtTitle;
	ref<TextBlock> m_txtTip;
	ref<Node2D> m_tipParent;
	ref<TextBlock> m_txtTipTitle;
	ref<TextBlock> m_txtTipContent;

	PathType m_pathType;
	std::string m_name;
};

class EditCardScene : public Node2D
{
public:
	EditCardScene();

	void setIndex(const Index &index);
	void setName(const std::string &name);
	void setParkingSlotType(ParkingSlotType psType);

	Event<EventArgs> BackToMain;
	Event<EventArgs> SaveCard;
	Event<Index> DeleteCard;

private:
	ref<Node2D> m_left;
	ref<Button> m_btnBackToMain;
	ref<TextBlock> m_txtTitle;
	ref<TextBlock> m_txtPsType;
	ref<Button> m_btnEdit;
	ref<Button> m_btnSave;
	ref<Button> m_btnDel;
	Index m_index;
};