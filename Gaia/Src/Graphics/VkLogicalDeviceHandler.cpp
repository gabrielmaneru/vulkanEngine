#include "GaiaPCH.h"
#include "VkLogicalDeviceHandler.h"

#include <Core/VkHandler.h>

namespace Gaia
{
	VkLogicalDeviceHandler::VkLogicalDeviceHandler(VkPhysicalDeviceHandler* physicalDeviceHandler)
	{
		VkPhysicalDeviceHandler::QueueFamilyIndices indices = physicalDeviceHandler->findQueueFamilies();

		float queuePriority = 1.0f;
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies = {
			indices.graphicsFamily.value(),
			indices.presentFamily.value()
		};

		// Fill queue create info for every queue family
		for (uint32_t queueFamily : uniqueQueueFamilies)
		{
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		// Those are the required features, we can leave it empty for now
		VkPhysicalDeviceFeatures deviceFeatures{};

		// Fill device create info
		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos = queueCreateInfos.data();
		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = 0;

		// Enable validation layers
		if (VkHandler::EnableValidationLayers)
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(VkHandler::ValidationLayers.size());
			createInfo.ppEnabledLayerNames = VkHandler::ValidationLayers.data();
		}
		else
		{
			createInfo.enabledLayerCount = 0;
		}

		if (vkCreateDevice(physicalDeviceHandler->getPhysicalDevice(), &createInfo, nullptr, &this->logicalDevice) != VK_SUCCESS)
			throw std::runtime_error("Failed to create logical device!");

		vkGetDeviceQueue(this->logicalDevice, indices.graphicsFamily.value(), 0, &this->graphicsQueue);
		vkGetDeviceQueue(this->logicalDevice, indices.presentFamily.value(), 0, &this->presentQueue);
	}
	VkLogicalDeviceHandler::~VkLogicalDeviceHandler()
	{
		vkDestroyDevice(this->logicalDevice, nullptr);
	}
}
