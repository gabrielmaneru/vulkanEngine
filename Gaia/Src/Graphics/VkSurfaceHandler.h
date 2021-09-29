#pragma once

namespace Gaia
{
	class VkSurfaceHandler
	{
	public:
		VkSurfaceHandler(GLFWwindow* window, VkInstance instance);
		~VkSurfaceHandler();

	private:
		VkSurfaceKHR surface = VK_NULL_HANDLE;
	};
}