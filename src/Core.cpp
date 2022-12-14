#include "./Core.h"
#include "./CPS.hpp"

#include "./utils/settings.h"
#include "./manager/Worker.h"

#include <windows.h>

void Core::Loader()
{
	Settings settings(std::string("./config.ini"), false);
	settings.load();

	CPS::cps = settings.getValue<float>("cps");
	CPS::setBind(settings.getValue("bind"));

	CPS::random = settings.getValue<bool>("random_cps");
	CPS::bounds[0] = settings.getValue<float>("min");
	CPS::bounds[1] = settings.getValue<float>("max");
	CPS::press_delay = settings.getValue<float>("press_delay");
	
	log("[INFO] Config file loaded.\n\n");

	log("[CONFIG] Desired CPS: %.1f.\n", CPS::cps);
	log("[CONFIG] Press delay: %.1f.\n", CPS::press_delay);
	log("[CONFIG] Bind: %s.\n", settings.getValue("bind").c_str());

	log("[CONFIG] Random CPS: %s.\n", CPS::random ? "true" : "false");
	if (CPS::random)
		log("[CONFIG] Min CPS: %.1f.\n", CPS::bounds[0]);
	if (CPS::random)
		log("[CONFIG] Max CPS: %.1f.\n", CPS::bounds[1]);

	CPS::initialize = true;

	log("\n[INFO] Press 'DEL' to exit.\n");

	do
	{

		if (GetAsyncKeyState(VK_DELETE) & 0x1)
		{
			Worker::Done = true;
		}

		delay(10);
	} while (Worker::Done == false);
}