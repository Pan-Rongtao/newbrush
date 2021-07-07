#include "ImGuiHelper.h"
#include <stdio.h>
#include "imgui/imgui_impl/imgui_impl_glfw.h"
#include "imgui/imgui_impl/imgui_impl_opengl3.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "newbrush/Types.h"

using namespace rttr;
using namespace nb;

ImGuiView::ImGuiView(GLFWwindow * window)
{
	if (!window)
	{
		glfwSetErrorCallback([](int error, const char* description) { fprintf(stderr, "Glfw Error %d: %s\n", error, description); });
		glfwInit();

		auto monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		window = glfwCreateWindow(mode->width, mode->height, "newbrush studio", nullptr, nullptr);

		glfwMaximizeWindow(window);
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1); // Enable vsync
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}
	m_window = window;

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	// Setup Platform/Renderer backends; GL 3.0 + GLSL 130
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
}

void ImGuiView::beginFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	//ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	int display_w, display_h;
	glfwGetFramebufferSize(m_window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	//	glClear(GL_COLOR_BUFFER_BIT);
}

void ImGuiView::endFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	//for multi-viewport
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}

static bool g_enableRender = true;
void ImGuiHelper::render(ImGuiView * view)
{
	if (!view || !g_enableRender)
		return;

	static bool viewInited = false;
	if (!viewInited)
	{
		view->onInit();
		viewInited = true;
	}

	view->beginFrame();
	view->onRender();
	view->endFrame();
}

int ImGuiHelper::run(ImGuiView * view)
{
	if (!view)
		return -1;

	auto window = view->getWindow();
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		ImGuiHelper::render(view);

		glfwSwapBuffers(window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void ImGuiHelper::enableRender(bool enable)
{
	g_enableRender = enable;
}

bool ImGuiHelper::isEnableRender()
{
	return g_enableRender;
}

void ImGuiWidget::showPropertyEditor(instance &obj)
{
	rttr::type type = obj.get_type().is_wrapper() ? obj.get_wrapped_instance().get_derived_type().get_raw_type() : obj.get_type();
	auto typeName = type ? type.get_name().data() : "";
	auto props = type ? type.get_properties() : array_range<property>();

	//header
	ImVec2 button_sz(40, 40);
	ImGui::Button("", button_sz);
	ImGui::SameLine();
	ImGui::Dummy(ImVec2(5, 5)); ImGui::SameLine();
	ImGui::Text(typeName);
	ImGui::SameLine();
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted("");
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}

	ImGui::Separator();

	ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.50f);
	for (auto const &prop : props)
	{
		auto propType = prop.get_type();
		const char *propName = prop.get_name().data();

		if (propType == type::get<bool>())						{ auto &v = prop.get_value(obj).get_value<bool>(); ImGui::Checkbox(propName, &v); bool b = prop.set_value(obj, v); }
		else if (propType == type::get<char>())					{ auto &v = prop.get_value(obj).get_value<char>(); ImGui::DragScalar(propName, ImGuiDataType_S8, &v, 1, NULL, NULL); bool b = prop.set_value(obj, v); }
		else if (propType == type::get<unsigned char>())		{ auto &v = prop.get_value(obj).get_value<unsigned char>(); ImGui::DragScalar(propName, ImGuiDataType_U8, &v, 1, NULL, NULL); bool b = prop.set_value(obj, v); }
		else if (propType == type::get<short>())				{ auto &v = prop.get_value(obj).get_value<short>(); ImGui::DragScalar(propName, ImGuiDataType_S16, &v, 1, NULL, NULL); bool b = prop.set_value(obj, v); }
		else if (propType == type::get<unsigned short>())		{ auto &v = prop.get_value(obj).get_value<unsigned short>(); ImGui::DragScalar(propName, ImGuiDataType_U16, &v, 1, NULL, NULL); bool b = prop.set_value(obj, v); }
		else if (propType == type::get<int>())					{ auto &v = prop.get_value(obj).get_value<int>(); ImGui::DragScalar(propName, ImGuiDataType_S32, &v, 1, NULL, NULL); bool b = prop.set_value(obj, v); }
		else if (propType == type::get<unsigned int>())			{ auto &v = prop.get_value(obj).get_value<unsigned int>(); ImGui::DragScalar(propName, ImGuiDataType_U32, &v, 1, NULL, NULL); bool b = prop.set_value(obj, v); }
		else if (propType == type::get<long long>())			{ auto &v = prop.get_value(obj).get_value<long long>(); ImGui::DragScalar(propName, ImGuiDataType_S64, &v, 1, NULL, NULL); bool b = prop.set_value(obj, v); }
		else if (propType == type::get<unsigned long long>())	{ auto &v = prop.get_value(obj).get_value<unsigned long long>(); ImGui::DragScalar(propName, ImGuiDataType_U64, &v, 1, NULL, NULL); bool b = prop.set_value(obj, v); }
		else if (propType == type::get<float>())				{ auto &v = prop.get_value(obj).get_value<float>(); ImGui::DragScalar(propName, ImGuiDataType_Float, &v, 0.1f, NULL, NULL, "%.3f"); bool b = prop.set_value(obj, v); }
		else if (propType == type::get<double>())				{ auto &v = prop.get_value(obj).get_value<double>(); ImGui::DragScalar(propName, ImGuiDataType_Double, &v, 0.1f, NULL, NULL, "%.6f"); bool b = prop.set_value(obj, v); }
		else if (propType == type::get<std::string>())			{ auto v = prop.get_value(obj).get_value<std::string>(); char buf[256] = {}; memcpy(buf, v.data(), v.size()); ImGui::InputText(propName, &buf[0], IM_ARRAYSIZE(buf)); bool b = prop.set_value(obj, std::string(buf)); }
		else if (propType == type::get<glm::vec2>())			{ auto &v = prop.get_value(obj).get_value<glm::vec2>(); ImGui::DragFloat2(propName, (float*)&v); bool b = prop.set_value(obj, v); }
		else if (propType == type::get<glm::vec3>())			{ auto v = prop.get_value(obj).get_value<glm::vec3>(); ImGui::DragFloat3(propName, (float*)&v); bool b = prop.set_value(obj, v); }
		else if (propType == type::get<glm::vec4>())			{ auto v = prop.get_value(obj).get_value<glm::vec4>(); ImGui::DragFloat4(propName, (float*)&v); bool b = prop.set_value(obj, v); }
		else if (propType == type::get<Point>())				{ auto v = prop.get_value(obj).get_value<Point>(); ImGui::DragFloat2(propName, (float*)&v); bool b = prop.set_value(obj, v); }
		else if (propType == type::get<Point3D>())				{ auto v = prop.get_value(obj).get_value<Point3D>(); ImGui::DragFloat3(propName, (float*)&v); bool b = prop.set_value(obj, v); }
		else if (propType == type::get<Size>())					{ auto v = prop.get_value(obj).get_value<Size>(); ImGui::DragFloat2(propName, (float*)&v); bool b = prop.set_value(obj, v); }
		else if (propType == type::get<Rect>())					{ auto v = prop.get_value(obj).get_value<Rect>(); ImGui::DragFloat4(propName, (float*)&v); bool b = prop.set_value(obj, v); }
		else if (propType == type::get<Color>())				{ auto v = prop.get_value(obj).get_value<Color>(); float f[4] = { v.r / 255.0f, v.g / 255.0f, v.b / 255.0f, v.a / 255.0f }; ImGui::ColorEdit4(propName, (float*)&f); bool b = prop.set_value(obj, Color::fromRgbaF(f[0], f[1], f[2], f[3])); }
		else if (propType == type::get<Thickness>())			{ auto v = prop.get_value(obj).get_value<Thickness>(); ImGui::DragFloat4(propName, (float*)&v); bool b = prop.set_value(obj, v); }
		else if (propType == type::get<TimeSpan>())				{ auto v = prop.get_value(obj).get_value<TimeSpan>(); int i[6] = { v.days(), v.hours(), v.minutes(), v.seconds(), v.milliseconds(), v.microseconds() }; ImGui::DragScalarN(propName, ImGuiDataType_S32, (int*)&i, IM_ARRAYSIZE(i), 1.0f); bool b = prop.set_value(obj, TimeSpan(i[0], i[1], i[2], i[3], i[4], i[5])); }
		//else if (propType == type::get<Date>())					{ auto v = prop.get_value(obj).get_value<Date>(); int i[3] = { v.year(), v.month(), v.day() }; ImGui::DragScalarN(propName, ImGuiDataType_S32, (int*)&i, IM_ARRAYSIZE(i), 1.0f); bool b = prop.set_value(obj, Date(i[0], i[1], i[2])); }
		else if (propType.is_enumeration())
		{
			auto e = propType.get_enumeration();
			std::vector<std::string> names(e.get_names().begin(), e.get_names().end());
			auto bytes = 1;
			for (auto &n : names) bytes += (n.size() + 1);

			char *str = new char[bytes];
			int i = 0;
			for (auto const &name : names)
			{
				memcpy(str + i, name.data(), name.size());
				str[i + name.size()] = 0;
				i = i + name.size() + 1;
			}
			str[bytes - 1] = 0;

			static int item_current = 0;
			ImGui::Combo(propName, &item_current, (const char*)str);
		}
	}
}
