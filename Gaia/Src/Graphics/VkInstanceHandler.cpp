#include "GaiaPCH.h"
#include "VkInstanceHandler.h"

#include <Core/VkHandler.h>

namespace Gaia
{
	VkInstanceHandler::VkInstanceHandler()
	{
		// Fill application info
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Triangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		// Fill instance create info
		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		auto extensions = getRequiredExtensions();
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();

		// Enable validation layers
		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
		if (VkHandler::EnableValidationLayers)
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(VkHandler::ValidationLayers.size());
			createInfo.ppEnabledLayerNames = VkHandler::ValidationLayers.data();

			VkHandler::PopulateDebugMessengerCreateInfo(debugCreateInfo);
			createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
		}
		else
		{
			createInfo.enabledLayerCount = 0;
			createInfo.pNext = nullptr;
		}

		// Create the VkInstance
		if (vkCreateInstance(&createInfo, nullptr, &this->instance) != VK_SUCCESS)
			throw std::runtime_error("Failed to create VkInstance");

	}
	VkInstanceHandler::~VkInstanceHandler()
	{
		vkDestroyInstance(this->instance, nullptr);
	}


	/// <summary>
	/// Gets the required extensions for the current setup
	/// </summary>
	std::vector<const char*> VkInstanceHandler::getRequiredExtensions()
	{
		uint32_t glfwExtensionCount;
		const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		if (VkHandler::EnableValidationLayers)
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

		return extensions;
	}
}
