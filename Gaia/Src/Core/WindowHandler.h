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

	private:
		GLFWwindow* window;
	};
}