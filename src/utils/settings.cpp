#include "./settings.h"

void Settings::load()
{
    readContent();

    if (dbg)
        for (auto const &[key, val] : database)
        {
            LOG("Settings (%s) -> %s\n", key.c_str(), val.c_str());
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
            LOG("CAN'T FIND CONFIG FILE, CREATING ONE\n");

        createDefaultFile();
        loadFromFile();
    }
    else
    {
        if (dbg)
            LOG("CONFIG FILE OPENED\n");
    }
}

void Settings::set(std::string key, std::string val)
{
    auto f = std::ofstream(__path, std::ios_base::binary | std::ios::app);

    if (!f.is_open()) // COULDNT CREATE FILE
    {
        if (dbg)
            LOG("CAN'T CREATE CONFIG FILE, EXITING\n");
        exit(EXIT_FAILURE);
    }

    std::stringstream ss;
    ss << key;
    ss << " = ";
    ss << val;
    ss << "\n";

    f << ss.rdbuf();
    f.close();

    loadFromFile();
    readContent();
}

void Settings::createDefaultFile()
{
    auto nf = std::ofstream(__path, std::ios_base::binary);
    if (!nf.is_open()) // COULDNT CREATE FILE
    {
        if (dbg)
            LOG("CAN'T CREATE CONFIG FILE, EXITING\n");
        exit(EXIT_FAILURE);
    }

    if (dbg)
        LOG("CONFIG FILE CREATED\n");
    std::stringstream ss;
    ss << "#AUTO GENERATED V1\n#FOR BIND USE https://pastebin.com/Etmtbm2C\n\n";
    nf << ss.rdbuf();
    nf.close();

    set("bind", "VK_XBUTTON2");
    set("cps", std::to_string(10));
    set("press_delay", std::to_string(20));
    set("random_cps", "false");
    set("min", std::to_string(10));
    set("max", std::to_string(15));
}

void Settings::readContent()
{
    if (!isOpen())
    {
        if (dbg)
            LOG("CAN'T READ CONFIG FILE CONTENT BECAUSE FILE IS NOT OPEN\n");
        return;
    }

    if (dbg)
        LOG("READING CONFIG FILE\n");

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
                        LOG("Pushing (%s) -> %s\n", key.c_str(), val.c_str());
                    database.insert({key, val});
                }
            }
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