#pragma once

namespace Gaia
{
	class VkInstanceHandler
	{
	public:
		VkInstanceHandler();
		~VkInstanceHandler();

		VkInstance getInstance() const { return this->instance; }

	private:
		static std::vector<const char*> getRequiredExtensions();

		VkInstance instance;
	};
}