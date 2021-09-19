#include "GaiaPCH.h"
#include "WinHandler.h"

namespace Gaia
{
	WinHandler::WinHandler()
	{
		if (glfwInit() != GLFW_TRUE)
			throw std::runtime_error("Failed to initialize GLFW");

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		this->window = glfwCreateWindow(this->Width, this->Height, "Vulkan", nullptr, nullptr);
		if (this->window == nullptr)
			throw std::runtime_error("Failed to create Window");
	}

	WinHandler::~WinHandler()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}


	void WinHandler::PollEvents()
	{
		glfwPollEvents();
	}

	bool WinHandler::ShouldClose()
	{
		return glfwWindowShouldClose(this->window);
	}
}
