#include "GaiaPCH.h"
#include "WindowHandler.h"

namespace Gaia
{
	WindowHandler::WindowHandler()
	{
		if (glfwInit() != GLFW_TRUE)
			throw std::runtime_error("Failed to initialize GLFW");

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		this->window = glfwCreateWindow(this->Width, this->Height, "Vulkan", nullptr, nullptr);
		if (this->window == nullptr)
			throw std::runtime_error("Failed to create Window");
	}

	WindowHandler::~WindowHandler()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}


	void WindowHandler::Update()
	{
		glfwPollEvents();
	}

	bool WindowHandler::ShouldClose()
	{
		return glfwWindowShouldClose(this->window);
	}
}
