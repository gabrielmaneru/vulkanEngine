#pragma once

struct GLFWwindow;
namespace Gaia
{
	class WinHandler
	{
	public:
		WinHandler();
		~WinHandler();

		void PollEvents()const;
		bool ShouldClose()const;
		GLFWwindow* GetWindow()const { return this->window; }


		const unsigned int Width = 1920;
		const unsigned int Height = 1080;

	private:
		GLFWwindow* window;
	};
}