#include "ModelBrowser.h"

using namespace nb;

bool g_useBkg = true;

void ModelBrowser::init()
{
	m_scene = createRef<Scene>();
	ViewBase::loadModel(m_scene, RES_DIR"/models/a08/fbx.fbx",glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.015f));
	m_data = buildData();
	binding();

	if(g_useBkg)
		loadBackground(m_scene, RES_DIR"/models/skybox1/");

	if (m_data)
	{
		m_data->ValueChanged += [&](const DataContext::ValueChangedArgs & args)
		{
			onDataChanged(args.path, args.value);
		};
	}
}

ref<Node> ModelBrowser::getRoot()
{
	return m_scene;
}

void ModelBrowser::onDataChanged(const std::string &path, const var &value)
{
	if (path == "AllSwitch") //动画总开关数据
	{
		bool bOn = value.get_value<bool>();
		for (auto sb : m_scene->animations)
		{
			for (auto tl : sb->children())
			{
				tl->reverse = !bOn;
			}
		}

		for (auto ani : m_scene->animations)
		{
			ani->begin();
		}
	}
	else if (path.size() >= 5 && path.substr(0, 4) == "Door")	//动画开关数据"Door*Switch"
	{
		size_t animationIndex = path[4] - 48 - 1;
		auto ani = (m_scene->animations.empty() || animationIndex >= m_scene->animations[0]->children().size())
			? nullptr : m_scene->animations[0]->children()[animationIndex];
		if (ani)
		{
			ani->reverse = !value.get_value<bool>();
			ani->begin();
		}
	}
	else if (path == "NewPath") //更换模型数据（由于涉及到OGL的api调用，如果是android端，需要MessageQueue转到SurfaceView渲染线程
	{
		auto newModelPath = value.get_value<std::string>();
		auto task = [this, newModelPath]()
		{
			m_scene->clearChildren();
			m_scene->animations.clear();
			m_scene->lights.clear();
			ViewBase::loadModel(m_scene, newModelPath, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.015f));

			if (g_useBkg)
				loadBackground(m_scene, RES_DIR"/models/skybox1/");
			//重新加载模型，场景发送变化，需重新绑定
			binding();
		};

#ifdef __ANDROID__
		MessageQueue::get()->post(task);	//android下post消息
#else
		task();
#endif

	}
}

void ModelBrowser::onKey(int key)
{
	auto model = m_scene->getChildAt(0);
	auto light = m_scene->lights.empty() ? nullptr : nb::as<PointLight>(m_scene->lights[0]);
	auto camera = m_scene->getCamera();
	Log::info("key[{}] press", key);
	auto modelTranslate = model->getTranslate();
	auto modelRotate = model->getRotate();
	auto cameraRotate = camera->getRotate();

	switch (key)
	{
	case 'W':	modelTranslate.y += 0.1f; model->setTranslate(modelTranslate);	break;
	case 'S':	modelTranslate.y -= 0.1f; model->setTranslate(modelTranslate);	break;
	case 'A':	modelTranslate.x -= 0.1f; model->setTranslate(modelTranslate);	break;
	case 'D':	modelTranslate.x += 0.1f; model->setTranslate(modelTranslate);	break;
	case 'Z':	modelTranslate.z += 0.1f; model->setTranslate(modelTranslate);	break;
	case 'X':	modelTranslate.z -= 0.1f; model->setTranslate(modelTranslate);	break;
	case 'R':	modelRotate.y -= 0.1f; model->setRotate(modelRotate);	break;
	case 'T':	modelRotate.y += 0.1f; model->setRotate(modelRotate);	break;
	case 'F':	modelRotate.x += 0.1f; model->setRotate(modelRotate);	break;
	case 'G':	modelRotate.x -= 0.1f; model->setRotate(modelRotate);	break;

	case '1':	setData("NewPath", RES_DIR"/models/a08/fbx.fbx");		break;
	case '2':	setData("NewPath", RES_DIR"/models/am8/fbx.fbx");		break;
	case '3':	setData("NewPath", RES_DIR"/models/assassin/fbx.fbx");	break;
	case '4':	setData("NewPath", RES_DIR"/models/bmw/fbx.fbx");		break;
	case '5':	setData("NewPath", RES_DIR"/models/bugatti/fbx.fbx");	break;
	case '6':	setData("NewPath", RES_DIR"/models/nanosuit/obj.obj");	break;
	case '7':	setData("NewPath", RES_DIR"/models/siqi/fbx.fbx");		break;
	case '8':	setData("NewPath", RES_DIR"/models/xueli/fbx.fbx");		break;
	case '9':	setData("NewPath", RES_DIR"/models/a08/fbx.fbx");		break;
	case '0':	setData("NewPath", RES_DIR"/models/a08/fbx.fbx");		break;

	case 'J':	cameraRotate.y += 0.1f; camera->setRotate(cameraRotate);break;
	case 'L':	cameraRotate.y -= 0.1f; camera->setRotate(cameraRotate);break;
	case 'K':	cameraRotate.x += 0.1f; camera->setRotate(cameraRotate);break;
	case 'I':	cameraRotate.x -= 0.1f; camera->setRotate(cameraRotate);break;
		//上下左右按键
	case 262:	if (light) light->position.x += 1;						break;
	case 263:	if (light) light->position.x -= 1;						break;
	case 264:	if (light) light->position.y -= 1;						break;
	case 265:	if (light) light->position.y += 1;						break;

	case 320:
	{
		auto bOn = m_data->lookup("AllSwitch")->get().get_value<bool>();
		setData("AllSwitch", !bOn);
	}
	break;
	case 321: case 322: case 323: case 324: case 325: case 326: //小键盘1~6设置动画开关数据
	{
		std::string doorDataPath = "Door" + std::to_string(key - 320) + "Switch";
		auto bOn = m_data->get(doorDataPath)->get().get_value<bool>();
		setData(doorDataPath, !bOn);
	}
	break;
	case 330:
	{
		if (m_scene->childCount() != 0)
			changeMaterial(m_scene->getChildAt(0));
	}
	break;
	case 45: case 61:
	{
		auto scale = m_data->lookup("Scale")->get().get_value<glm::vec3>();
		auto newScale = key == 45 ? scale - glm::vec3(0.002f) : scale + glm::vec3(0.002f);
		setData("Scale", newScale);
	}
	break;
	case 335:
	{
		if (m_scene->lights.empty())	return;

		auto target = m_scene->lights[0];
		auto targetProperty = type::get<Light>().get_property("Ambient");
		m_lightAnimation.beginTime = TimeSpan::fromSeconds(1);
		m_lightAnimation.duration = TimeSpan::fromSeconds(10);
		m_lightAnimation.setTarget(target);
		m_lightAnimation.setTargetProperty(targetProperty);
		m_lightAnimation.keyFrames().insert(ColorKeyFrame(TimeSpan::fromSeconds(0), Colors::red));
		m_lightAnimation.keyFrames().insert(ColorKeyFrame(TimeSpan::fromSeconds(1), Colors::green));
		m_lightAnimation.keyFrames().insert(ColorKeyFrame(TimeSpan::fromSeconds(3), Colors::blue));
		m_lightAnimation.begin();
	}
	case 331:
	{
		//m_scene->camera->projectionType = ProjectionType::Orthographic;
		//auto scale = m_scene->children[0]->transform->getScale() * 20.0f;
		//m_scene->children[0]->transform->setScale(scale);
	}
	break;
	default: break;
	}
}

ref<DataObject> ModelBrowser::buildData()
{
	auto data = nb::makeDataObject("root");
	data->add(makeDataColor("Ambient", Color(127, 127, 127)));
	data->add(makeDataColor("Diffuse", Color(127, 127, 127)));
	data->add(makeDataColor("Specular", Color(127, 127, 127)));
	data->add(makeDataVec3("LightPosition", glm::vec3(0.0f, 0.0f, 5.0f)));
	data->add(makeDataVec3("Translate", glm::vec3(0.0f, -0.0f, 0.0f)));
	data->add(makeDataVec3("Rotate", glm::vec3(0.0f, 0.0f, 0.0f)));
	data->add(makeDataVec3("Scale", glm::vec3(0.020f)));
	data->add(makeDataBool("AllSwitch", false));
	data->add(makeDataBool("Door1Switch", false));
	data->add(makeDataBool("Door2Switch", false));
	data->add(makeDataBool("Door3Switch", false));
	data->add(makeDataBool("Door4Switch", false));
	data->add(makeDataBool("Door5Switch", false));
	data->add(makeDataBool("Door6Switch", false));
	data->add(makeDataString("NewPath", ""));
	return data;
}

void ModelBrowser::binding()
{
	if (!m_scene || !m_data)	return;

	auto target = m_scene->lights[0];
	BindingMaster::clear();
	BindingMaster::addBinding(target, type::get<PointLight>().get_property("Ambient"), createRef<Binding>(m_data, "Ambient"));
	BindingMaster::addBinding(target, type::get<PointLight>().get_property("Diffuse"), createRef<Binding>(m_data, "Diffuse"));
	BindingMaster::addBinding(target, type::get<PointLight>().get_property("Specular"), createRef<Binding>(m_data, "Specular"));
	BindingMaster::addBinding(target, type::get<PointLight>().get_property("Position"), createRef<Binding>(m_data, "LightPosition"));

	auto target1 = m_scene->getChildAt(0);
	BindingMaster::addBinding(target1, type::get<Node>().get_property("Translate"), createRef<Binding>(m_data, "Translate"));
	BindingMaster::addBinding(target1, type::get<Node>().get_property("Rotate"), createRef<Binding>(m_data, "Rotate"));
	BindingMaster::addBinding(target1, type::get<Node>().get_property("Scale"), createRef<Binding>(m_data, "Scale"));

}

//一定不要少了这句
ref<ViewBase> g_view = createRef<ModelBrowser>();
