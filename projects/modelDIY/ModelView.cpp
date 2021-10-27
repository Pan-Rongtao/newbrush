#include "ModelView.h"
#include "MainView.h"

ModelView::ModelView()
{
	setSize({ 650, 720 });
	//setBackground(SolidColorBrush::red());
	Touch += nbBindEventFunction(ModelView::onTouch);

	auto scene = createRef<Scene>();
	scene->addLight(createRef<PointLight>());
	setScene(scene);

	load(ModelType::XiaoV);
}

void ModelView::load(ModelType type)
{
	m_type = type;
	auto scene = getScene();
	if (type == ModelType::XiaoV)
	{
		if(!m_xiaovModel)
			m_xiaovModel = loadModel(RES_DIR"/modelDIY/xiaov/1.fbx", glm::vec3(0.0f, -2.3f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.030f));

		scene->clearChildren();
		scene->addChild(m_xiaovModel);
		m_xiaovModel->play();
	}
	else if (type == ModelType::DIY)
	{
		if (!m_diyModel)
		{
			auto camera = scene->getCamera();
			auto translate = camera->getTranslate();
			auto rotate = camera->getRotate();
			translate.y = -0.08f;
			rotate.x = 0.1f;
			camera->setTranslate(translate);
			camera->setRotate(rotate);

			m_diyModel = loadModel(RES_DIR"/modelDIY/diy/1.fbx", glm::vec3(0.0f, -3.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.030f));
			MainView::get()->diyNode->initDresses();

			auto hairStandar0Material = createRef<PhongMaterial>();
			hairStandar0Material->emissionColor = { 128, 128, 128 };
			hairStandar0Material->emissionMapping = createRef<Texture2D>(RES_DIR"/modelDIY/diy/baked-polySurfaceShape9.png");
			auto zhamaoMaterial = createRef<PhongMaterial>();
			zhamaoMaterial->emissionColor = { 128, 128, 128 };
			zhamaoMaterial->emissionMapping = createRef<Texture2D>(RES_DIR"/modelDIY/diy/baked-ZhaMaoShape.png");
			auto ceMaterial = createRef<PhongMaterial>();
			ceMaterial->emissionColor = { 128, 128, 128 };
			ceMaterial->emissionMapping = createRef<Texture2D>(RES_DIR"/modelDIY/diy/baked-hair_CeShape.png");
			auto bianMaterial = createRef<PhongMaterial>();
			bianMaterial->emissionColor = { 128, 128, 128 };
			bianMaterial->emissionMapping = createRef<Texture2D>(RES_DIR"/modelDIY/diy/baked-pSphereShape17.png");
			auto smallMaterial = createRef<PhongMaterial>();
			smallMaterial->emissionColor = { 128, 128, 128 };
			smallMaterial->emissionMapping = createRef<Texture2D>(RES_DIR"/modelDIY/diy/baked-pSphereShape19.png");
			auto mouseMiaoMaterial = createRef<PhongMaterial>();
			mouseMiaoMaterial->emissionColor = { 128, 128, 128 };
			mouseMiaoMaterial->emissionMapping = createRef<Texture2D>(RES_DIR"/modelDIY/diy/baked-polySurface408Shape.png");
			auto mouseCloseMaterial = createRef<PhongMaterial>();
			mouseCloseMaterial->emissionColor = { 128, 128, 128 };
			mouseCloseMaterial->emissionMapping = createRef<Texture2D>(RES_DIR"/modelDIY/diy/baked-Mouth_closeShape.png");
			auto mouseHahaMaterial = createRef<PhongMaterial>();
			mouseHahaMaterial->emissionColor = { 128, 128, 128 };
			mouseHahaMaterial->emissionMapping = createRef<Texture2D>(RES_DIR"/modelDIY/diy/baked-Mouth_HaHa1Shape.png");
			auto yifuAMaterial = createRef<PhongMaterial>();
			yifuAMaterial->emissionColor = { 128, 128, 128 };
			yifuAMaterial->emissionMapping = createRef<Texture2D>(RES_DIR"/modelDIY/diy/baked-YiFu_A_polySurface9_polySurface9Shape.png");
			auto shoesBlackMaterial = createRef<PhongMaterial>();
			shoesBlackMaterial->emissionColor = { 128, 128, 128 };
			shoesBlackMaterial->emissionMapping = createRef<Texture2D>(RES_DIR"/modelDIY/diy/baked-polySurface398Shape.png");
			auto shoesBoyMaterial = createRef<PhongMaterial>();
			shoesBoyMaterial->emissionColor = { 128, 128, 128 };
			shoesBoyMaterial->emissionMapping = createRef<Texture2D>(RES_DIR"/modelDIY/diy/baked-polySurface229Shape.png");
			m_diyModel->setMaterial("polySurface10", hairStandar0Material);
			m_diyModel->setMaterial("ZhaMao", zhamaoMaterial);
			m_diyModel->setMaterial("hair_Ce", ceMaterial);
			m_diyModel->setMaterial("pSphere17", bianMaterial);
			m_diyModel->setMaterial("pSphere21", bianMaterial);
			m_diyModel->setMaterial("pSphere20", smallMaterial);
			m_diyModel->setMaterial("pSphere19", smallMaterial);
			m_diyModel->setMaterial("polySurface408", mouseMiaoMaterial);
			m_diyModel->setMaterial("Mouth_close", mouseCloseMaterial);
			m_diyModel->setMaterial("Mouth_HaHa1", mouseHahaMaterial);
			m_diyModel->setMaterial("polySurface9", yifuAMaterial);
			m_diyModel->setMaterial("polySurface397", shoesBlackMaterial);
			m_diyModel->setMaterial("polySurface398", shoesBlackMaterial);
			m_diyModel->setMaterial("polySurface229", shoesBoyMaterial);
			m_diyModel->setMaterial("polySurface399", shoesBoyMaterial);
		}

		scene->clearChildren();
		scene->addChild(m_diyModel);
		m_diyModel->play();
	}

}

ref<Model> ModelView::getModel()
{
	return m_type == ModelType::XiaoV ? m_xiaovModel : m_diyModel;
}

void ModelView::onTouch(const TouchEventArgs & e)
{
	Point p = { e.x, e.y };
	if (e.action == TouchAction::Down)
	{
		m_pressed = true;
		m_pressedPoint = p;
	}
	else if (e.action == TouchAction::Move)
	{
		if (!m_pressed) return;

		Point ptOffset = { p.x - m_pressedPoint.x, m_pressedPoint.y - p.y };
		m_pressedPoint = p;

		auto model = getModel();
		if (!model)
			return;

		auto rotate = model->getTransform()->getRotate();
		auto newAngle = glm::degrees(rotate.y) + ptOffset.x;
		rotate.y = glm::radians(newAngle);
		model->getTransform()->setRotate(rotate);
	}
	else if (e.action == TouchAction::Up)
	{
		m_pressed = false;
	}
}
