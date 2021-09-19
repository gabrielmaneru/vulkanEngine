#pragma once

namespace Gaia
{
	class VkHandler
	{
	public:
		VkHandler();
		~VkHandler();


	private:
		void createInstance();

		VkInstance instance;
	};
}