#include "GaiaPCH.h"
#include "VkHandler.h"

#include <Graphics/VkInstanceHandler.h>

namespace Gaia
{
	VkDebugUtilsMessengerEXT debugMessenger;

	VkHandler::VkHandler()
	{
		this->instanceHandler = new VkInstanceHandler();
	}
	VkHandler::~VkHandler()
	{
		delete this->instanceHandler;
	}
}
