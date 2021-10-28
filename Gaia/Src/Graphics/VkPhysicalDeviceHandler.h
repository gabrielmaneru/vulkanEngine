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
		struct SwapChainSupportDetails
		{
			VkSurfaceCapabilitiesKHR capabilities;
			std::vector<VkSurfaceFormatKHR> formats;
			std::vector<VkPresentModeKHR> presentModes;
		};

		QueueFamilyIndices findQueueFamilies()const { return findQueueFamilies(this->physicalDevice, this->surface); }
		SwapChainSupportDetails querySwapChainSupport() const { return querySwapChainSupport(this->physicalDevice, this->surface); }
		VkPhysicalDevice getPhysicalDevice()const { return this->physicalDevice; }
		VkSurfaceKHR getSurface()const { return this->surface; }
		QueueFamilyIndices getQueueIndices()const { return findQueueFamilies(this->physicalDevice, this->surface); }


	private:
		static int rateDeviceSuitability(VkPhysicalDevice device, VkSurfaceKHR surface);
		static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
		static bool checkDeviceExtensionSupport(VkPhysicalDevice device);
		static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);

		VkSurfaceKHR surface = VK_NULL_HANDLE;
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	};
}