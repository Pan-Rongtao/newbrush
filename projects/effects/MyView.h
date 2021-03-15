#pragma once
#include "newbrush/Controls.h"
#include "newbrush/Application.h"
#include "newbrush/StateManager.h"
#include "newbrush/Animation.h"

using namespace nb;

class MyView
{
public:
	MyView();

	ref<Node2D> getRoot();



	ref<Node2D> m_root;
};