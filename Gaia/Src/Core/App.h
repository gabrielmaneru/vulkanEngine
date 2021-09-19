#pragma once

namespace Gaia
{
	class WinHandler;
	class VkHandler;
	class App
	{
	public:
		virtual bool Initialize();
		virtual void Shutdown();
		void Run();

	private:
		WinHandler* windowHandler = nullptr;
		VkHandler* vkHandler = nullptr;
	};
}