#pragma once

namespace Gaia
{
	class VkSurfaceHandler
	{
	public:
		VkSurfaceHandler(GLFWwindow* window, VkInstance instance);
		~VkSurfaceHandler();

		VkSurfaceKHR GetSurface()const { return surface; }

	private:
		VkInstance instance = VK_NULL_HANDLE;
		VkSurfaceKHR surface = VK_NULL_HANDLE;
	};
}