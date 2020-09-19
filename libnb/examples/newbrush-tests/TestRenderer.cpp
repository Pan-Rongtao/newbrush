#include "newbrush/gui/Window.h"
#include "newbrush/gui/Application.h"
#include "newbrush/rvl/gles/Renderer.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"
#include "catch2/catch.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include "GLFW/glfw3.h"
#include <GLES2/gl2.h>

using namespace nb;

TEST_CASE("test Renderer", "[Renderer]") {

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

	auto renderObj = std::make_shared<Renderer3D>();
	renderObj->setProgram(Programs::model());
	renderObj->load("../model/car.fbx", "../model");

	renderObj->storeUniform("light.position", glm::vec3(0.0f, 0.0f, 5.0f));
	renderObj->storeUniform("viewPos", glm::vec3(0.0f, 0.0f, 3.0f));
	renderObj->storeUniform("light.ambient", glm::vec3(0.5f, 0.5f, 0.5f));
	renderObj->storeUniform("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	renderObj->storeUniform("light.specular", glm::vec3(0.5f, 0.5f, 0.5f));
	
	enum WindowType
	{
		WINDOW2D = 0,
		WINDOW3D
	};

	WindowType windowType = WINDOW2D;
	auto camera = std::make_shared<Camera>();

	if (windowType == WINDOW2D) {
		camera->ortho(0.0f, (float)WIDTH, (float)HEIGHT, 0.0f, -1000.0f, 1000.0f);
	}
	else if (windowType == WINDOW3D) {
		camera->lookat(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		camera->perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	}

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model = glm::mat4(1.0f);
		
		if (windowType == WINDOW2D) {
			float strength{ 20.0f };
			model = glm::translate(model, { 400, 300, 0 });
			model = glm::scale(model, glm::vec3(strength, strength, strength));
			model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		else if (windowType == WINDOW3D) {
			float strength{ 0.0015f };
			model = glm::scale(model, glm::vec3(strength, strength, strength));
			model = glm::rotate(model, (GLfloat)glfwGetTime()*0.5f, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		
		//renderObj->model()->matrix = model;
		renderObj->draw(camera);

		glfwSwapBuffers(window);
	}
	glfwTerminate();
}