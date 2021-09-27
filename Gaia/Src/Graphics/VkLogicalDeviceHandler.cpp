#include "GaiaPCH.h"
#include "VkLogicalDeviceHandler.h"

#include <Core/VkHandler.h>

namespace Gaia
{
	VkLogicalDeviceHandler::VkLogicalDeviceHandler(VkPhysicalDeviceHandler* physicalDeviceHandler)
	{
		// Fill queue create info
		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		auto indices = physicalDeviceHandler->getQueueIndices();
		queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
		queueCreateInfo.queueCount = 1;
		float queuePriority = 1.0f;
		queueCreateInfo.pQueuePriorities = &queuePriority;

		// Those are the required features, we can leave it empty for now
		VkPhysicalDeviceFeatures deviceFeatures{};

		// Fill device create info
		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos = &queueCreateInfo;
		createInfo.queueCreateInfoCount = 1;
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
	}
	VkLogicalDeviceHandler::~VkLogicalDeviceHandler()
	{
		vkDestroyDevice(this->logicalDevice, nullptr);
	}
}
