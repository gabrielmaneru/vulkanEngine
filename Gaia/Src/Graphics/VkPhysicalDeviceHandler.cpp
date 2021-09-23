#include "GaiaPCH.h"
#include "VkPhysicalDeviceHandler.h"

namespace Gaia
{
	VkPhysicalDeviceHandler::VkPhysicalDeviceHandler(VkInstance instance)
	{
		// Check if any GPU is supported
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
		if (deviceCount == 0)
			throw std::runtime_error("Failed to find GPUs with Vulkan support!");

		// Get the collection of GPUs
		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

		// Check if any GPU is suitable
		std::multimap<int, VkPhysicalDevice> candidates;
		for (const auto& device : devices)
		{
			if (int score = rateDeviceSuitability(device) > 0)
				candidates.insert(std::make_pair(score, device));
		}
		if (candidates.empty())
			throw std::runtime_error("Failed to find a suitable GPU!");
		this->physicalDevice = candidates.rbegin()->second;
	}

	VkPhysicalDeviceHandler::~VkPhysicalDeviceHandler()
	{
	}

	int VkPhysicalDeviceHandler::rateDeviceSuitability(VkPhysicalDevice device)
	{
		VkPhysicalDeviceProperties deviceProperties;
		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);
		vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
		int score = 0;

		// Pick first discrete GPU
		if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
			score += 1000;
		return score;
	}
}
