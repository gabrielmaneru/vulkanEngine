#pragma once

struct GLFWwindow;
namespace Gaia
{
	class WinHandler
	{
	public:
		WinHandler();
		~WinHandler();

		void PollEvents();
		bool ShouldClose();

		const unsigned int Width = 1920;
		const unsigned int Height = 1080;

	private:
		GLFWwindow* window;
	};
}