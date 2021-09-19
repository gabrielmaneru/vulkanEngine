#pragma once

namespace Gaia
{
	class WindowHandler;
	class App
	{
	public:
		virtual bool Initialize();
		virtual void Shutdown();
		void Run();

	private:
		WindowHandler* windowHandler = nullptr;
	};
}