#include "newbrush/gui/Window.h"
#include "newbrush/gui/Application.h"
#include "newbrush/gles/RenderObject.h"
#include "newbrush/gles/Program.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"
#include "catch2/catch.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include "newbrush/gles/Shader.h"
#include "GLFW/glfw3.h"
#include <GLES2/gl2.h>

using namespace nb;

TEST_CASE("test RenderObject", "[RenderObject]") {

	const GLuint WIDTH = 800, HEIGHT = 600;
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
	renderObj->setProgram(Programs::model());
	renderObj->loadFromFile("../model/car.fbx", "../model");
	
	Camera camera;
	Projection projection;
	float strength;	//用来调整渲染对象的缩放比例

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//2D窗口展示：
	projection.matrix = glm::ortho(-(float)WIDTH / 2, (float)WIDTH / 2, -(float)HEIGHT / 2, (float)HEIGHT / 2, -1000.0f, 1000.0f);
	strength = 20.0f;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//3D窗口展示：
	//camera.lookat(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//projection.perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	//strength = 0.0015f;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderObj->draw(camera, projection);
		
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(strength, strength, strength));
		//model = glm::rotate(model, (GLfloat)glfwGetTime()*0.5f, glm::vec3(0.0f, 1.0f, 0.0f));
		renderObj->model()->matrix = model;

		glfwSwapBuffers(window);
	}
	glfwTerminate();
}