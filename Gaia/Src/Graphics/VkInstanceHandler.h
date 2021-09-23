#pragma once

namespace Gaia
{
	class VkInstanceHandler
	{
	public:
		VkInstanceHandler();
		~VkInstanceHandler();

	private:
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		static bool checkValidationLayerSupport();
		static std::vector<const char*> getRequiredExtensions();
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);

		VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger;

#ifdef GAIA_DEBUG
		static const bool enableValidationLayers = true;
#else
		static const bool enableValidationLayers = false;
#endif // DEBUG
		static const std::vector<const char*> validationLayers;
	};
}