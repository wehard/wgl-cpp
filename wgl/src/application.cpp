#include "application.h"
#include "camera.h"
#include "renderer.h"
#include "input.h"
#include "framebuffer.h"
#include "mesh.h"
#include "texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "bitmap_font.h"
#include "text.h"
#include <vector>
#include <string>

namespace wgl
{

Application *Application::instance = nullptr;

Application::Application(std::string title, int windowWidth, int windowHeight) : title(title), windowWidth(windowWidth), windowHeight(windowHeight), wireframe_mode(0)
{
	instance = this;
	init();
}

Application::Application() {}

Application::~Application() {}

void Application::init()
{
	if (!glfwInit())
		std::cout << "GLFW failed to initialize!" << std::endl;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	window = glfwCreateWindow(windowWidth, windowHeight, title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
		std::cout << "GLEW failed to initialize!" << std::endl;
	camera = new Camera(45.0f, (float)windowWidth / (float)windowHeight);
	renderer = new Renderer(camera);
	Input::setupKeyInputs(window);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_FALSE);
	glEnable(GL_DEPTH_TEST);
}

void Application::run()
{
	// Framebuffer *frameBuffer = new Framebuffer(1280, 720);
	input = new Input(std::vector<int>({GLFW_KEY_W}));

	onAttach();
	last_time = glfwGetTime();
	double fps_time = last_time;
	int frameCount = 0;
	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		if (input->isKeyDown(GLFW_KEY_W))
			wireframe_mode = !wireframe_mode;
		double current_time = glfwGetTime();
		double delta_time = current_time - last_time;
		if (current_time - fps_time > 1.0)
		{
			int fps = frameCount / fps_time;
			std::string windowTitle = title + " " + std::to_string(fps) + " fps";
			glfwSetWindowTitle(this->window, windowTitle.c_str());
			fps_time = current_time;
		}

		onUpdate(delta_time);

		for (auto e : entities)
			e->update(delta_time);

		// rendering into framebuffer
		// frameBuffer->Bind();

		glClearColor(0.2, 0.2, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (wireframe_mode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		for (auto e : entities)
			renderer->drawEntity(e);
		for (auto t : texts)
			renderer->drawText(t);

		// frameBuffer->Unbind();

		// display framebuffer
		// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		// glClearColor(0.0, 0.0, 0.0, 1.0);
		// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// frameBuffer->draw();

		glfwSwapBuffers(window);
		last_time = current_time;
		frameCount++;
		glfwPollEvents();
	}
}

void Application::addEntity(Entity *e)
{
	entities.insert(entities.begin(), e);
	e->id = entities.size();
}

void Application::addText(Text *text)
{
	texts.insert(texts.end(), text);
}

} // namespace wgl