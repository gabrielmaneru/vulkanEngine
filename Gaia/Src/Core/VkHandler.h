#pragma once

namespace Gaia
{
	class VkInstanceHandler;
	class VkPhysicalDeviceHandler;

	class VkHandler
	{
	public:
		VkHandler();
		~VkHandler();

	private:
		VkInstanceHandler* instanceHandler;
		VkPhysicalDeviceHandler* physicalDeviceHandler;
	};
}