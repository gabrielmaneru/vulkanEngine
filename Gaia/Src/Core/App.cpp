#include "GaiaPCH.h"
#include "App.h"

#include "WindowHandler.h"

namespace Gaia
{
	bool App::Initialize()
	{
		try
		{
			this->windowHandler = new WindowHandler();
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
			this->windowHandler->Update();
		} while (!this->windowHandler->ShouldClose());
	}

	void App::Shutdown()
	{
		delete this->windowHandler;
	}
}
