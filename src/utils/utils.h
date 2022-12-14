#ifndef UTILS_H

#define delay(x) std::this_thread::sleep_for(std::chrono::milliseconds(x))
#define log(x, ...) printf(x, ##__VA_ARGS__)

#define UTILS_H
#endif