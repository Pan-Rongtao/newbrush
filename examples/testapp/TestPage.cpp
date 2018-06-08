#include "TestPage.h"
#include "Gui/Grid.h"
#include "Gui/Rectangle.h"
#include "Gui/Image.h"
#include "Gui/SolidColorBrush.h"
#include "System/ObjectBelongingFactoryCollection.h"
#include "Core/ObjectAttachmentSymbol.h"

using namespace nb::Gui;
using namespace nb::Core;
using namespace nb::System;

//RefObjectPtr xx()
//{
//	RefObjectPtr ptr;
//	return ptr;
//}

class aa
{
public:
	int a;
};

class bb : public aa
{
public:

	virtual void xxxx() {}
	int b;
};

#include "System/Platform.h"


class AbcFarCallServer;
//AbcFarCallServer *g_fcServer;
nbObjectPtrDerive<AbcFarCallServer, nbObjectPtr> g_fcServer;

class AbcFarCallClient : public nb::System::FarCallClient
{
	virtual void SendDataOverride(FarCallSerial &dataSerial, FarCallSerial &resultSerial);

};

class AbcFarCallServer : public nb::System::FarCallServer
{
public:
	AbcFarCallClient *m_pClient;
	void SendDataOverride(FarCallSerial &dataSerial, FarCallSerial &resultSerial)
	{
	//	FarCallDataSendExceptionPtr ex = new nb::System::FarCallDataSendException("²âÊÔÊ§°Ü");
	//	throw ex;

		m_pClient->AcceptData(dataSerial.GetBuffer(), dataSerial.GetDataSize(), resultSerial);
	}
};

class AbcConnectObjectSv;
nbObjectPtrDerive<AbcConnectObjectSv, nbObjectPtr> s_pSvObject;
class AbcConnectObjectSv : public AbcConnectObject
{
public:
	AbcConnectObjectSv()
	{
		s_pSvObject = this;
	}

	virtual GenericVariant TestSv(TestParam &param)
	{
		return GenericVariant(20);
	}
};

void AbcFarCallClient::SendDataOverride(FarCallSerial &dataSerial, FarCallSerial &resultSerial)
{
	g_fcServer->AcceptData(dataSerial.GetBuffer(), dataSerial.GetDataSize(), resultSerial);

	//resultSerial.
}

class aabb
{
public:
	//int x[20];
	std::vector<int> x;

	aabb() {x.resize(20);}
	void SetAt(int index, int v){x[index] = v;}
};

void TestPage::OnFFTestEvent(AbcConnectObject::TestEventParam &param)
{
	param.m_r1 = 1;
}


TestPage::TestPage(void)
{
	g_fcServer = new AbcFarCallServer();
	g_fcServer->RegServer<AbcConnectObjectSv>("Abc");
	AbcFarCallClient fcClient;
	g_fcServer->m_pClient = &fcClient;


	AbcConnectObject abc(&fcClient);
	AbcConnectObject::TestParam testParam;
//	g_fcServer->Close();
	int ksdf = abc.Test(testParam);

	abc.TestEvent.Add(this, &TestPage::OnFFTestEvent);

	AbcConnectObject::TestEventParam testEventParam;
//	abc.TestEvent.Send(testEventParam);
//	s_pSvObject->TestEvent.Send(testEventParam);


//	g_fcServer->Close();
	try{
		abc.TestEvet2.Add(this, &TestPage::OnFFTestEvent);
		s_pSvObject->TestEvet2.Send(testEventParam);
	}
	catch(nb::System::FarCallDataSendExceptionPtr ex)
	{
		int a =0;
		a++;
	}



		nb::Gui::TestObjectEx xx;
		xx.a();


	nb::Gui::RectanglePtr r1 = new nb::Gui::Rectangle();
	r1->Widthex = 20;
	float x = r1->Widthex;

	nb::Gui::RectanglePtr r2 = new nb::Gui::Rectangle();

//	nb::Media::BrushPtr brush = new nb::Media::SolidColorBrush();
//	r1->Fill = brush;
//	r2->Fill = brush;

//	brush->NotifyContentChanged();

/*	PV<nb::Media::Brush> pv;

	nb::Media::BrushPtr brush = new nb::Media::SolidColorBrush();
	pv = brush;

	PV<nb::Media::Brush> pv1;
	pv1 = brush;

//	pv1 = NULL;

	PV<nb::Media::Brush> pv2;
	pv2 = brush;

	pv = NULL;

	PV<nb::Media::Brush> pv3;
	pv3 = brush;//*/


	int tick = 0;
	int k = 0;
	k++;
/*	tick = nb::System::Platform::GetTickCount();

	for(int i=0; i<100000; i++)
	{
		aabb ab;
	//	for(int k =0;k<20; k++)
	//		ab.SetAt(k, 20);
	}
	tick = nb::System::Platform::GetTickCount() - tick;
	tick++;

	tick = nb::System::Platform::GetTickCount();
//*/

	nb::Gui::RectanglePtr r = new nb::Gui::Rectangle();
//	for(int i=0; i<100000; i++)
	{
		r->SetRefValue(r->WidthexProperty(), new aFloat(10));
		r->Widthex = 10;
		float z = r->Widthex;
		r->Widthex->ToString();

	//	r.Get();

	//	new nbObject();
	}

	tick = nb::System::Platform::GetTickCount() - tick;
	tick++;

//	r->SetRefValue(r->
//	r->SetRockPV(r->WidthexProperty(), 10);

//	int *k1 = &((aa *)NULL)->a;
//	int *k2 = &((bb *)NULL)->a;

	// ×Ö·û´®±È½ÏÐÔÄÜ
//	String a = "asdf";
//	String b = "vdewr";
//	std::string a = "asdf";
//	std::string b = "vdewr";

//	int xx1 = GetTickCount();
//	for(int i=0; i<1000000; i++)
//	{
//		a < b;
//	}
//	xx1 = GetTickCount() - xx1;
//	xx1++;



//	int a = 0;
//	a++;
//	RefObjectPtr zz;
//	zz = xx();

/*	ObjectAttachmentSymbolPtr s = new ObjectAttachmentSymbol();
	ObjectAttachmentSymbolPtr s1 = new ObjectAttachmentSymbol();
	nbObjectPtr b0 = new nbObject();
	nbObjectPtr b1 = new nbObject();
	nbObjectPtr zzz = new nbObject();
	zzz->SetAttachment(s, b0);
	zzz->SetAttachment(s1, b1, true);
	zzz->SetAttachment(s1, b1, false);
	b0 = NULL;
	RefObjectPtr sdf = zzz->GetAttachment(s);
	RefObjectPtr sdf1 = zzz->GetAttachment(s1);//*/

/*	ObjectBelongingFactoryPtr factory = new ObjectBelongingFactoryT<Grid>();

	// RowDefCollection
	ObjectBelongingFactory* rowDefCollectionFactory = new ObjectBelongingFactoryT<RowDefinitionCollection>();
	factory->SetRefValue(Grid::GetRowDefCollectionProperty(), rowDefCollectionFactory);

	ObjectBelongingFactory* rowDefFactory = new ObjectBelongingFactoryT<RowDefinition>();
	rowDefFactory->SetValueValue(RowDefinition::GetHeightProperty(), GridLength(0.3, GridLength::UnitType_Star));

	rowDefCollectionFactory->Children()->Add(rowDefFactory);

	// ColDefCollection
	ObjectBelongingFactory* colDefCollectionFactory = new ObjectBelongingFactoryT<ColDefinitionCollection>();
	factory->SetRefValue(Grid::GetColDefCollectionProperty(), colDefCollectionFactory);

	ObjectBelongingFactory* child = new ObjectBelongingFactoryT<nb::Gui::Rectangle>();
	factory->Children()->Add(child);

	child->SetRefValue(nb::Gui::Rectangle::GetFillProperty(), new nb::Media::SolidColorBrush(nb::System::Color(155, 0, 0)));
//	r->Margin() = nb::Gui::Thickness(5, 20, 5, 10);

//	child = new ObjectBelongingFactoryT<nb::Gui::Rectangle>();
//	factory->Children()->Add(child);

	Grid *createObject = (Grid *)factory->CreateObject();
	SetRootPanel(createObject);
//*/


//	nb::Core::RefObject* p = factory;
//	x.Insert(0, p);


//	nb::Gui::Grid *g = new Grid();
//	nb::Core::InterfaceBase *x = NULL;
//	dynamic_cast<nb::System::IHasChildrenArray *>(x);
//	nb::System::IHasChildrenArray *p = g->GetInterface<nb::System::IHasChildrenArray>();
//	p->GetChildrenArray();

	nb::Gui::GridPtr grid = new nb::Gui::Grid();
	SetRootPanel(grid);

//	grid->RowDefCollection() = new RowDefinitionCollection();
	RowDefinitionCollection *rowColl =  grid->RowDefCollection;//->RowDefCollection()->Add(new RowDefinition());

	RowDefinition *rd = new RowDefinition();
	rd->Height() = GridLength(0.3, GridLength::UnitType_Star);
	rowColl->Add(rd);

	rd = new RowDefinition();
	rd->Height() = GridLength(0, GridLength::UnitType_Auto);
	rowColl->Add(rd);

	rd = new RowDefinition();
	rd->Height() = GridLength(0.3, GridLength::UnitType_Star);
	rowColl->Add(rd);


	//Cols
//	grid->ColDefCollection() = new ColDefinitionCollection();
	ColDefinitionCollection *colColl =  grid->ColDefCollection;

	ColDefinition *cd = new ColDefinition();
	cd->Width() = GridLength(0.3, GridLength::UnitType_Star);
	colColl->Add(cd);

	cd = new ColDefinition();
	cd->Width() = GridLength(0, GridLength::UnitType_Auto);
	colColl->Add(cd);

	cd = new ColDefinition();
	cd->Width() = GridLength(50, GridLength::UnitType_Length);
	colColl->Add(cd);

//	int k = ::GetTickCount();
	for(int i=0; i<1; i++)
	{
	nb::Gui::RectanglePtr r;

	//1
	r = new nb::Gui::Rectangle();


	if(r->Widthex.IsNull())
	{
		int a = 0;
		a++;
	}

	//r->Fillex = new nb::Media::SolidColorBrush(nb::System::Color(120 ,0, 0));
//	int k = ::GetTickCount();
//	for(int t=0; t<20000; t++)
//	{
	r->SetRefValue(r->FillProperty(), new nb::Media::SolidColorBrush(nb::System::Color(120 ,120, 0)));
//	}
//	k = GetTickCount() - k;

//	r->Fill = new nb::Media::SolidColorBrush(nb::System::Color(155, 0, 0));
	r->Margin() = nb::Gui::Thickness(5, 20, 5, 10);
//	grid->AddChild(r);
	grid->Children()->Add(r);
	Grid::SetRow(r, 0);

//	nb::Gui::ImagePtr image = new Image();
//	image->SetSource(new ImageSource("c:\\a\\2.jpg"));

//	grid->Children()->Add(image);
//	Grid::SetRow(image, 1);
	}

//	k = GetTickCount() - k;
//*/
}

TestPage::~TestPage(void)
{
}
