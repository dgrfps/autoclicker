#include "./Core.h"
#include "./CPS.hpp"

#include "./utils/settings.h"
#include "./manager/Worker.h"

#include <windows.h>

void Core::Loader()
{
	Settings settings(std::string("./config.ini"), false);
	settings.load();

	CPS::cps = settings.getValue<float>("cps", 10);
	auto bind = settings.getValue<std::string>("bind", "VK_XBUTTON2");
	CPS::setBind(bind);

	CPS::random = settings.getValue<bool>("random_cps", false);
	CPS::bounds[0] = settings.getValue<float>("min", 10);
	CPS::bounds[1] = settings.getValue<float>("max", 15);
	CPS::press_delay = settings.getValue<float>("press_delay", 20);

	LOG("[INFO] Config file loaded.\n\n");

	LOG("[CONFIG] Bind: %s.\n", bind.c_str());
	LOG("[CONFIG] Desired CPS: %.1f.\n", CPS::cps);
	LOG("[CONFIG] Press delay: %.1f.\n", CPS::press_delay);
	LOG("[CONFIG] Random CPS: %s.\n", CPS::random ? "true" : "false");
	if (CPS::random)
		LOG("[CONFIG] CPS Range: [%.1f., %.1f.]\n", CPS::bounds[0], CPS::bounds[1]);

	CPS::initialize = true;

	LOG("\n[INFO] Press 'DEL' to exit.\n");

	do
	{

		if (GetAsyncKeyState(VK_DELETE) & 0x1)
		{
			Worker::Done = true;
		}

		delay(10);
	} while (Worker::Done == false);
}