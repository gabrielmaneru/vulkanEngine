#include "GaiaPCH.h"
#include "App.h"

#include "WinHandler.h"
#include "VkHandler.h"

namespace Gaia
{
	bool App::Initialize()
	{
		try
		{
			this->windowHandler = new WinHandler();
			this->vkHandler = new VkHandler();
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			return false;
		}
		return true;
	}

	void App::Run()
	{
		do
		{
			this->windowHandler->PollEvents();
		} while (!this->windowHandler->ShouldClose());
	}

	void App::Shutdown()
	{
		delete this->vkHandler;
		delete this->windowHandler;
	}
}
