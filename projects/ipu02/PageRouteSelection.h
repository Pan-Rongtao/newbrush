#pragma once

#include "PageBase.h"

using namespace nb;

enum CardType
{
	NEWCARD = 0,
	CARDCOMPLETED,
	CARDSAVING,
	CARDLEARNING,
	CARDFAIL
};

class Card : public Node2D
{
public:
	Card(const Rect &rc, CardType cardtype);
	Card(float x, float y, float w, float h, CardType cardtype);
	CardType cardtype();

	void onTriggerCardToPage(NBPageID pageid);

	class CardToPageEventArgs : public EventArgs
	{
	public:
		NBPageID m_pageid;
	};
	nb::Event<CardToPageEventArgs> CardToPageEvent;
protected:
	void init();

protected:
	ref<DataContext> m_data;
	CardType m_cardtype;
};

class NewCard : public Card
{
public:
	NewCard(const Rect &rc, CardType cardtype);
	NewCard(float x, float y, float w, float h, CardType cardtype);
	void onBtnClicked(const EventArgs &arg);

protected:
	void init();

private:
	ref<TextBlock> m_txtcardtitle;

	ref<Node2D> m_btnrouteinbg;
	ref<TextBlock> m_txtroutein;
	ref<Button> m_btnroutein;

	ref<Node2D> m_btnrouteoutbg;
	ref<TextBlock> m_txtrouteout;
	ref<Button> m_btnrouteout;
};

class CardCompleted : public Card
{
public:
	CardCompleted(const Rect &rc, CardType cardtype);
	CardCompleted(float x, float y, float w, float h, CardType cardtype);
	void onBtnClicked(const EventArgs &arg);

protected:
	void init();

private:
	ref<TextBlock> m_txtcardtitle;

	ref<TextBlock> m_txtcardcontent;

	ref<Node2D> m_btnstartbg;
	ref<TextBlock> m_txtstart;
	ref<Button> m_btnstart;
};

class CardFail : public Card
{
public:
	CardFail(const Rect &rc, CardType cardtype);
	CardFail(float x, float y, float w, float h, CardType cardtype);
	void onBtnClicked(const EventArgs &arg);

protected:
	void init();

private:
	ref<TextBlock> m_txtcardtitle;

	ref<TextBlock> m_txtcardcontent;

	ref<Node2D> m_btndeletebg;
	ref<TextBlock> m_txtdelte;
	ref<Button> m_btndelete;
};

class PageRouteSelection : public PageBase
{
	using PageBase::PageBase;
public:
	PageRouteSelection(const Rect &rc, NBPageID id);
	PageRouteSelection(float x, float y, float w, float h, NBPageID id);
	void onBtnClicked(const EventArgs &arg);
	void onCardToPage(const Card::CardToPageEventArgs &args);
protected:
	void init();

private:
	ref<TextBlock> m_txtrouteselect;

	ref<Node2D> m_btncoursebg;
	ref<Node2D> m_btncourseicon;
	ref<TextBlock> m_txtcourse;
	ref<Button> m_btncourse;

	ref<Card> m_newcard;
	ref<Card> m_completedcard;
	ref<Card> m_failcard;
};