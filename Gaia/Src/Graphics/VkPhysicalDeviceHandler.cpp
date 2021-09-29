#include "GaiaPCH.h"
#include "VkPhysicalDeviceHandler.h"

namespace Gaia
{
	VkPhysicalDeviceHandler::VkPhysicalDeviceHandler(VkInstance instance, VkSurfaceKHR surface)
		: surface(surface)
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

	int VkPhysicalDeviceHandler::rateDeviceSuitability(VkPhysicalDevice device)const
	{
		VkPhysicalDeviceProperties deviceProperties;
		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);
		vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

		// If the device can't process the Graphics Queue commands, discard it
		QueueFamilyIndices indices = findQueueFamilies(device, surface);
		if (!indices.IsComplete())
			return 0;

		int score = 0;
		// Pick first discrete GPU
		if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
			score += 1000;
		return score;
	}
	VkPhysicalDeviceHandler::QueueFamilyIndices VkPhysicalDeviceHandler::findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface)
	{
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		int i = 0;
		QueueFamilyIndices indices;
		for (const auto& queueFamily : queueFamilies)
		{
			// Store Graphics queue
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
				indices.graphicsFamily = i;

			// Store Present queue
			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
			if (presentSupport)
				indices.presentFamily = i;

			if (indices.IsComplete())
				break;
			i++;
		}

		return indices;
	}
}
