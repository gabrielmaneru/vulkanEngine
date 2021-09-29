#pragma once

namespace Gaia
{
	class VkPhysicalDeviceHandler
	{
	public:
		VkPhysicalDeviceHandler(VkInstance instance, VkSurfaceKHR surface);

		struct QueueFamilyIndices
		{
			std::optional<uint32_t> graphicsFamily;
			std::optional<uint32_t> presentFamily;
			bool IsComplete(){
				return graphicsFamily.has_value()
				&& presentFamily.has_value(); }
		};
		QueueFamilyIndices findQueueFamilies()const { return findQueueFamilies(this->physicalDevice, this->surface); }
		static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
		VkPhysicalDevice getPhysicalDevice()const { return this->physicalDevice; }
		QueueFamilyIndices getQueueIndices()const { return findQueueFamilies(this->physicalDevice, this->surface); }

	private:
		int rateDeviceSuitability(VkPhysicalDevice device)const;

		VkSurfaceKHR surface = VK_NULL_HANDLE;
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	};
}