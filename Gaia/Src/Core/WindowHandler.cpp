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

		this->window = glfwCreateWindow(1920, 1080, "Vulkan", nullptr, nullptr);
		if (this->window == nullptr)
			throw std::runtime_error("Failed to create Window");

		u32 extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		if(extensionCount == 0)
			throw std::runtime_error("System is incompatible with Vulkan");
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
