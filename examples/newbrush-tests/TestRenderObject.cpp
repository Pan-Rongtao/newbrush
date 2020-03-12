#include "newbrush/gui/Window.h"
#include "newbrush/gui/Application.h"
#include "newbrush/gles/RenderObject.h"
#include "catch2/catch.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include "newbrush/gles/Shader.h"
#include "GLFW/glfw3.h"
#include <GLES2/gl2.h>

using namespace nb;

TEST_CASE("test RenderObject", "[RenderObject]") {

	const GLuint WIDTH = 1280, HEIGHT = 720;
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, WIDTH, HEIGHT);

	auto renderObj = std::make_shared<RenderObject>();
	renderObj->loadFromFile("D:/share/myProject/modelLoading/resources/objects/models/car.fbx");
	renderObj->setMaterial(std::make_shared<Material>(Programs::model()));

	while (!glfwWindowShouldClose(window)) {
		//GLfloat currentFrame = glfwGetTime();

		glfwPollEvents();//检查事件
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//状态设置函数
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//状态应用函数

		Camera camera;
		Projection projection;
		renderObj->draw(camera, projection);
		glfwSwapBuffers(window);
		//renderObj->storeUniform("color", glm::vec4(0.5f, 0.2f, 0.1f, 1.0f));
	}
	glfwTerminate();
}