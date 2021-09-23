#pragma once

namespace Gaia
{
	class VkPhysicalDeviceHandler
	{
	public:
		VkPhysicalDeviceHandler(VkInstance instance);
		~VkPhysicalDeviceHandler();

	private:
		static int rateDeviceSuitability(VkPhysicalDevice device);

		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	};
}