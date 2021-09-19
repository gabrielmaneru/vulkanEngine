#pragma once

struct GLFWwindow;
namespace Gaia
{
	class WindowHandler
	{
	public:
		WindowHandler();
		~WindowHandler();

		void Update();
		bool ShouldClose();

		const unsigned int Width = 1920;
		const unsigned int Height = 1080;

	private:
		GLFWwindow* window;
	};
}