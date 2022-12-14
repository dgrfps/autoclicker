#include "./Core.h"
#include "./CPS.hpp"
#include "./manager/Worker.h"

int main(int argc, char *argv[])
{
	Worker worker;
	worker.AddWorker(Core::Loader); // Main thread
	worker.AddWorker(CPS::init);
	worker.Init();
}