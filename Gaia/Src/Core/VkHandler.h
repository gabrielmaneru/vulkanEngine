#pragma once

namespace Gaia
{
	class VkInstanceHandler;

	class VkHandler
	{
	public:
		VkHandler();
		~VkHandler();

	private:
		VkInstanceHandler* instanceHandler;
	};
}