#include "./settings.h"

void Settings::load()
{
    readContent();

    if (dbg)
        for (auto const &[key, val] : database)
        {
            log("Settings (%s) -> %s\n", key.c_str(), val.c_str());
        }
}

Settings::Settings(std::string path, bool debug)
{
    this->__path = path;
    this->dbg = debug;

    loadFromFile();
}

void Settings::loadFromFile()
{
    file = std::fstream(__path, std::ios_base::in | std::ios_base::binary);

    if (!isOpen()) // File doesnt exit
    {
        if (dbg)
            log("CAN'T FIND CONFIG FILE, CREATING ONE\n");

        createFile();
        loadFromFile();
    }
    else
    {
        if (dbg)
            log("CONFIG FILE OPENED\n");
    }
}

void Settings::createFile()
{
    auto nf = std::ofstream(__path, std::ios_base::binary);
    if (!nf.is_open()) // COULDNT CREATE FILE
    {
        if (dbg)
            log("CAN'T CREATE CONFIG FILE, EXITING\n");
        exit(EXIT_FAILURE);
    }

    if (dbg)
        log("CONFIG FILE CREATED\n");
    std::stringstream ss;

    ss << "#AUTO GENERATED V1\n#FOR BIND USE https://pastebin.com/Etmtbm2C\n\n";
   
    ss << "cps = 10\n";
    ss << "press_delay = 5\n";
    ss << "bind = VK_XBUTTON1\n";
    ss << "random_cps = false\n";
    ss << "min = 1\n";
    ss << "max = 10\n";
    nf << ss.rdbuf();
    nf.close();
}

void Settings::readContent()
{
    if (!isOpen())
    {
        if (dbg)
            log("CAN'T READ CONFIG FILE CONTENT BECAUSE FILE IS NOT OPEN");
        return;
    }

    if (dbg)
        log("READING CONFIG FILE\n");

    std::string line;
    while (getline(file, line))
    {
        std::istringstream is_line(line);
        std::string key;

        if (!line.starts_with('#'))
            if (getline(is_line, key, '='))
            {
                std::string val;
                if (getline(is_line, val))
                {
                    if (key.ends_with(' '))
                        key = key.substr(0, key.size() - 1);
                    if (val.starts_with(' '))
                        val = val.substr(1, val.size());

                    if (dbg)
                        log("Pushing (%s) -> %s\n", key.c_str(), val.c_str());
                    database.insert({key, val});
                }
            }
    }
}

std::string Settings::getValue(std::string key)
{
    try
    {
        return database.at(key);
    }
    catch (const std::out_of_range &e)
    {
        if (dbg)
            log("[CONFIG] CANNOT FIND KEY %s\n  -> %s \n -> Returning null\n", key.c_str(), e.what());
        return "";
    }
}

void Settings::close()
{
    file.close();
}

bool Settings::isOpen()
{
    return file.is_open();
}