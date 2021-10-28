#pragma once

#include "VkPhysicalDeviceHandler.h"
#include "VkLogicalDeviceHandler.h"
namespace Gaia
{
	class VkSwapChainHandler
	{
	public:
		VkSwapChainHandler(VkPhysicalDeviceHandler* physicalDevice, VkDevice logicalDevice, uint32_t width, uint32_t height);
		~VkSwapChainHandler();

	private:
		static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, uint32_t width, uint32_t height);

		VkSwapchainKHR swapChain = VK_NULL_HANDLE;
		VkDevice device = VK_NULL_HANDLE;

		std::vector<VkImage> swapChainImages;
		VkFormat swapChainFormat;
		VkExtent2D swapChainExtent;
	};
}