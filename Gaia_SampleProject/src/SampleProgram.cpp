#include <Gaia.h>


class SampleApp : public Gaia::App
{
public:
	bool Initialize()override
	{
		if (!App::Initialize())
			return false;

		//.. SampleApp Initialize
		return true;
	}
	void Shutdown()override
	{
		//.. SampleApp Shutdown
		App::Shutdown();
	}
private:

};

SetEntryApp(SampleApp)
