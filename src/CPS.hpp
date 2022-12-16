#pragma once

#include <atomic>
#include <windows.h>

#include "./utils/utils.h"
#include "./manager/Worker.h"

#include "./Core.h"

#include <random>

class CPS
{
public:
    inline static float cps;
    inline static float bounds[2] = {0, 0};

    inline static double press_delay;

    inline static std::atomic_bool random;

    inline static int bind;

    inline static void setBind(std::string f) { bind = (int)keyboard_get_virtual_key_code_from_name(f.c_str()); };

    inline static void click()
    {
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        delay(static_cast<long int>(press_delay));
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    }
    inline static int range(int min, int max)
    {
        std::random_device rd;                           // obtain a random number from hardware
        std::mt19937 gen(rd());                          // seed the generator
        std::uniform_int_distribution<> distr(min, max); // define the range

        return distr(gen);
    }

    inline static void init()
    {
        do
        {
            delay(10);
        } while (initialize == false);

        do
        {
            if (GetAsyncKeyState(bind))
            {
                if (random)
                {
                    click();
                    delay(1000 / range(static_cast<long int>(bounds[0]), static_cast<long int>(bounds[1])));
                }
                else
                {
                    click();
                    delay(1000 / static_cast<long int>(cps));
                }
            }

        } while (Worker::Done == false);
    }
    inline static std::atomic_bool initialize;
};