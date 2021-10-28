#include "GaiaPCH.h"
#include "VkHandler.h"

#include <Core/WinHandler.h>
#include <Graphics/VkUtils.h>
#include <Graphics/VkInstanceHandler.h>
#include <Graphics/VkPhysicalDeviceHandler.h>
#include <Graphics/VkLogicalDeviceHandler.h>
#include <Graphics/VkSurfaceHandler.h>
#include <Graphics/VkSwapChainHandler.h>

namespace Gaia
{
	VkDebugUtilsMessengerEXT debugMessenger;
	const std::vector<const char*> VkHandler::ValidationLayers =
	{
		"VK_LAYER_KHRONOS_validation"
	};
	const std::vector<const char*> VkHandler::DeviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	VkHandler::VkHandler(WinHandler* windowHandler)
	{
		if (EnableValidationLayers && !checkValidationLayerSupport())
			throw std::runtime_error("Validation layers requested, but not available!");

		this->instanceHandler = new VkInstanceHandler();

		// Setup Debug Messenger
		if (EnableValidationLayers)
		{
			VkDebugUtilsMessengerCreateInfoEXT createInfo;
			PopulateDebugMessengerCreateInfo(createInfo);

			if (CreateDebugUtilsMessengerEXT(this->instanceHandler->getInstance(), &createInfo, nullptr, &debugMessenger) != VK_SUCCESS)
				throw std::runtime_error("Failed to set up debug messenger!");
		}

		this->surfaceHandler = new VkSurfaceHandler(windowHandler->GetWindow(), this->instanceHandler->getInstance());
		this->physicalDeviceHandler = new VkPhysicalDeviceHandler(this->instanceHandler->getInstance(), this->surfaceHandler->GetSurface());
		this->logicalDeviceHandler = new VkLogicalDeviceHandler(this->physicalDeviceHandler);

		this->swapChainHandler = new VkSwapChainHandler(physicalDeviceHandler, logicalDeviceHandler->getDevice(), windowHandler->Width, windowHandler->Height);
	}
	VkHandler::~VkHandler()
	{
		delete this->swapChainHandler;
		delete this->logicalDeviceHandler;
		delete this->physicalDeviceHandler;
		delete this->surfaceHandler;

		if (EnableValidationLayers)
			DestroyDebugUtilsMessengerEXT(this->instanceHandler->getInstance(), debugMessenger, nullptr);

		delete this->instanceHandler;
	}

	void VkHandler::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
	{
		createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		createInfo.messageSeverity =
			//VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		createInfo.messageType =
			VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		createInfo.pfnUserCallback = VkHandler::debugCallback;
	}
	/// <summary>
	/// Checks if the validation layer is supported
	/// </summary>
	bool VkHandler::checkValidationLayerSupport()
	{
		uint32_t layercount;
		vkEnumerateInstanceLayerProperties(&layercount, nullptr);
		std::vector<VkLayerProperties> availableLayers(layercount);
		vkEnumerateInstanceLayerProperties(&layercount, availableLayers.data());

		for (const char* layerName : ValidationLayers)
		{
			bool layerFound = false;
			for (const auto& layerProperties : availableLayers)
			{
				if (strcmp(layerName, layerProperties.layerName) == 0)
				{
					layerFound = true;
					break;
				}
			}
			if (!layerFound) return false;
		}
		return true;
	}

	/// <summary>
	/// Callback function for error messages
	/// </summary>
	VKAPI_ATTR VkBool32 VKAPI_CALL VkHandler::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
	{
		if (std::string(pCallbackData->pMessage).find("invalid layer manifest file version") != std::string::npos)
			return VK_FALSE;

		std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
		return VK_FALSE;
	}
}
