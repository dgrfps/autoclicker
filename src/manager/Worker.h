#pragma once

#include <vector>
#include <thread>
#include <atomic>

class Worker
{
public:
    void AddWorker(void (*v)())
    {
        workers.push_back(std::thread(v));
    }

    void Init()
    {
        for (std::thread &t : workers)
            if (t.joinable())
                t.join();
    }

    inline static std::atomic_bool Done;

private:
    std::vector<std::thread> workers;
};