#pragma once
#include "Definitions.h"
#include "App.h"

extern Gaia::App* CreateApp();

int main(int argc, char ** argv)
{
	auto app = CreateApp();
	if (app->Initialize())
	{
		app->Run();
		app->Shutdown();
	}
}