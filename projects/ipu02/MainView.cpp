﻿#include "MainView.h"
#include "newbrush/Log.h"
#include "AVMView.h"
#include "AIView.h"
#include "HPAView.h"

static MainView *g_instance = nullptr;

ref<Node2D> MainView::getCurrentView() const
{
	return m_current;
}

void MainView::init()
{
	g_instance = this;
	Application::get()->mainWindow()->setWidth(1920.0f);
	Application::get()->mainWindow()->setTitle("ipu02 Power By NewBrush");

#if NB_OS == NB_OS_QNX
	Application::get()->mainWindow()->setHeight(720.0f);
	m_root = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 720.0f);
#else
	Application::get()->mainWindow()->setHeight(1080.0f);
	Application::get()->mainWindow()->setPosition(0.0f, 0.0f);
	m_root = createRef<Node2D>(0.0f, 0.0f, 1920.0f, 1080.0f);
#ifndef WIN32
	m_root->setAlignmentCenter();
#endif
#endif

	m_root->setBackground(createRef<SolidColorBrush>(Color(238, 240, 245)));
	m_topBar = createRef<TopBar>();
	switchView<AVMView>();

	m_root->Key += [&](const KeyEventArgs &e)
	{
		switch (e.key)
		{
		case KeyCode::_1: ThemeManager::setTheme(0);	break;
		case KeyCode::_2: ThemeManager::setTheme(1);	break;
		case KeyCode::_8: LanguageManager::setLanguage(0);	break;
		case KeyCode::_9: LanguageManager::setLanguage(1);	break;
		default:											break;
		}
	};

	ThemeManager::ThemeChanged() += [&](const int &theme)
	{
		if (theme == 0)
		{
			m_root->setBackground(createRef<SolidColorBrush>(Color(238, 240, 245)));
		}
		else if (theme == 1)
		{
			m_root->setBackground(createRef<SolidColorBrush>(Color(0, 0, 0)));
		}

	};
}

MainView * MainView::get()
{
	return g_instance;
}

ref<TopBar> MainView::topbar()
{
	return m_topBar;
}

//一定不要少了这句
nb::ref<ViewBase> g_view = createRef<MainView>();
