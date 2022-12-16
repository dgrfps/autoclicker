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

    std::string getValue(std::string key, std::string def)
    {
        if (!database.contains(key))
            set(key, def);

        try
        {
            return database.at(key);
        }
        catch (const std::out_of_range &e)
        {
            if (dbg)
                LOG("[CONFIG] CANNOT FIND KEY %s\n  -> %s \n -> Returning null\n", key.c_str(), e.what());
            return "";
        }
    }

    template <typename T>
    T getValue(std::string key, T def)
    {
        std::ostringstream cDef;
        cDef << def;
        std::string sDef(cDef.str());
        // std::cout << key << " " << def << " " << sDef.c_str() << std::endl;

        std::istringstream ss(this->getValue(key, sDef)); // using this->getValue to reuse the catch exception
        T num;

        if (typeid(T).name() == typeid(bool).name())
            ss >> std::boolalpha >> num;
        else
            ss >> num;

        return (num);
    };
    void close();
    void load();

private:
    std::map<std::string, std::string> database;
    bool isOpen();

    void createDefaultFile();
    void readContent();
    void loadFromFile();

    void set(std::string key, std::string val);

    std::fstream file;
    std::string __path;

    bool dbg;
};

#define SETTINGS_H
#endif