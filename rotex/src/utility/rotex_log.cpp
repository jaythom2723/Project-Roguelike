//
// Created by pengu on 7/9/2025.
//

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <filesystem>
#include <algorithm>

#include "rotex_defs.h"

static std::ofstream logfile;

static const std::string LOG_HEADER_BOUNDARY = "=====================================================================================================\n";
static const std::string LOG_SEPARATOR       = "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
static const std::string LOG_HEADER[] = {
    LOG_HEADER_BOUNDARY,
    "[INFO] -> ... | An informational message, nothing to worry about.\n",
    "[WARNING] -> ... | A warning thrown by ROTEX. Usually doesn't lead to unusual behavior.\n",
    "[ERROR] -> ... | An error thrown by ROTEX. Mostly leads to undefined or unusual behavior.\n",
    "[FATAL] -> ... | Fatal error thrown by ROTEX. An error that prevents the program from continuing.\n",
    LOG_SEPARATOR,
};
static const std::string RT_LOG_TYPE_STRINGS[] = {
    "INFO",
    "WARNING",
    "ERROR",
    "FATAL"
};

// _ denotes private API functions that should never be exposed to the user (game programmer)
namespace rotex {
    static std::string _gen_path();
    bool _create_log_file();
    void _close_log_file();

    void _add_log_entry(const RTLogType type, const std::string& msg);
}

std::string rotex::_gen_path() {
    const time_t now = time(nullptr);
    const tm *ltm = localtime(&now);
    std::string date = asctime(ltm);
    date.erase(std::remove(date.begin(), date.end(), '\n'), date.end());
    return "log/" + date.substr(0, date.find(':')-3) + ".log";
}

// create a log file with the current date as the name with the extension .log
// should be created in the log/ directory within dist/bin/
bool rotex::_create_log_file() {
    const std::string path = _gen_path();

    logfile = std::ofstream();
    logfile.open(path.c_str(), std::ios::out);

    if (!logfile.is_open())
        return false;

    for (const std::string& msg : LOG_HEADER) {
        logfile << msg;
    }

    return true;
}

// called in rotex::close()
void rotex::_close_log_file() {
    logfile.close();
}

void rotex::_add_log_entry(const RTLogType type, const std::string &msg) {
    if (!logfile.is_open())
        return;

    const std::string entry = "[" + RT_LOG_TYPE_STRINGS[type] + "] -> " + msg + "\n";
    logfile << entry;
}
