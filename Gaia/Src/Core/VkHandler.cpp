#include "GaiaPCH.h"
#include "VkHandler.h"

#include <Graphics/VkInstanceHandler.h>
#include <Graphics/VkPhysicalDeviceHandler.h>

namespace Gaia
{
	VkDebugUtilsMessengerEXT debugMessenger;

	VkHandler::VkHandler()
	{
		this->instanceHandler = new VkInstanceHandler();
		this->physicalDeviceHandler = new VkPhysicalDeviceHandler(this->instanceHandler->getInstance());
	}
	VkHandler::~VkHandler()
	{
		delete this->instanceHandler;
	}
}
