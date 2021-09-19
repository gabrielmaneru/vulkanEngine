#pragma once
#define SetEntryApp(appClass)\
Gaia::App* CreateApp()    \
{                         \
	return new appClass();\
}
