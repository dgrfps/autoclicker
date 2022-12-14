#ifndef SETTINGS_H

#include <sstream>
#include <iostream>

#include <fstream>
#include <ostream>

#include <map>

#include "./utils.h"

class Settings
{
public:
    Settings(std::string path, bool debug);
    ~Settings()
    {
        file.close();
    }

    std::string getValue(std::string key);
    template <typename T>
    T getValue(std::string key)
    {
        std::istringstream ss(this->getValue(key)); // using this->getValue to reuse the catch exception
        T num;
        ss >> num;
        return (num);
    };
    void close();
    void load();

private:
    std::map<std::string, std::string> database;
    bool isOpen();

    void createFile();
    void readContent();
    void loadFromFile();

    std::fstream file;
    std::string __path;

    bool dbg;
};

#define SETTINGS_H
#endif