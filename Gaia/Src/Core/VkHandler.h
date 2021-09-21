#pragma once

namespace Gaia
{
	class VkHandler
	{
	public:
		VkHandler();
		~VkHandler();


	private:
		void createInstance();
		void setupDebugMessenger();

		static bool checkValidationLayerSupport();
		static std::vector<const char*> getRequiredExtensions();
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);

		VkInstance instance;

		#ifdef GAIA_DEBUG
		static const bool enableValidationLayers = true;
		#else
	    static const bool enableValidationLayers = false;
		#endif // DEBUG
		static const std::vector<const char*> validationLayers;
	};
}