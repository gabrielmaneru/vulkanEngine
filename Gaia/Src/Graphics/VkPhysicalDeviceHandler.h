#pragma once

namespace Gaia
{
	class VkPhysicalDeviceHandler
	{
	public:
		VkPhysicalDeviceHandler(VkInstance instance);


		struct QueueFamilyIndices
		{
			std::optional<uint32_t> graphicsFamily;
			std::optional<uint32_t> presentFamily;
			bool IsComplete(){ return
				graphicsFamily.has_value()
				&& presentFamily.has_value(); }
		};
		VkPhysicalDevice getPhysicalDevice()const { return this->physicalDevice; }
		QueueFamilyIndices getQueueIndices()const { return findQueueFamilies(this->physicalDevice); }

	private:
		static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		static int rateDeviceSuitability(VkPhysicalDevice device);

		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	};
}