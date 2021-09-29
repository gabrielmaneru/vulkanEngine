#include "GaiaPCH.h"
#include "VkSurfaceHandler.h"

namespace Gaia
{
	VkSurfaceHandler::VkSurfaceHandler(GLFWwindow* window, VkInstance instance)
	{
		this->instance = instance;

		if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS)
			throw std::runtime_error("Failed to create window surface!");
	}
	VkSurfaceHandler::~VkSurfaceHandler()
	{
		vkDestroySurfaceKHR(instance, surface, nullptr);
	}
}
