#pragma once
#include "VkPhysicalDeviceHandler.h"

namespace Gaia
{
	class VkLogicalDeviceHandler
	{
	public:
		VkLogicalDeviceHandler(VkPhysicalDeviceHandler* physicalDeviceHandler);
		~VkLogicalDeviceHandler();
		VkDevice getDevice()const { return this->logicalDevice; }

	private:
		VkDevice logicalDevice = VK_NULL_HANDLE;

		VkQueue presentQueue = VK_NULL_HANDLE;
		VkQueue graphicsQueue = VK_NULL_HANDLE;
	};
}