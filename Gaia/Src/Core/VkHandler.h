#pragma once

namespace Gaia
{
	class VkInstanceHandler;
	class VkPhysicalDeviceHandler;
	class VkLogicalDeviceHandler;
	class VkSurfaceHandler;
	class GLFWwindow;

	class VkHandler
	{
	public:
		VkHandler(GLFWwindow* window);
		~VkHandler();

#ifdef GAIA_DEBUG
		static const bool EnableValidationLayers = true;
#else
		static const bool EnableValidationLayers = false;
#endif // DEBUG
		static const std::vector<const char*> ValidationLayers;
		static void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

	private:
		VkInstanceHandler* instanceHandler;
		VkPhysicalDeviceHandler* physicalDeviceHandler;
		VkLogicalDeviceHandler* logicalDeviceHandler;
		VkSurfaceHandler* surfaceHandler;

		static bool checkValidationLayerSupport();
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);
	};
}