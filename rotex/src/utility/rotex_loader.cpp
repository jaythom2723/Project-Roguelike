//
// Created by pengu on 7/9/2025.
//

#include <string>
#include <iostream>

#include <toml/toml.hpp>

#include "rotex.h"
#include "rotex_defs.h"
#include "utility/rotex_data.h"

/*
    All things file loading!
*/
namespace rotex {
    // if required is true, should the toml parse fail, fatal error
    toml::table _parse_toml_file(const std::string& path, bool required);

    RTGameData* _propagate(const toml::table& tbl);

    extern void _add_log_entry(const RTLogType, const std::string& msg);
}

toml::table rotex::_parse_toml_file(const std::string& path, bool required) {
    toml::table tbl;
    RTLogType logType = RTLogType::ROTEX_LOG_INFO;

    _add_log_entry(logType, "Attempting to load TOML file (" + path + ").");
    try {
        tbl = toml::parse_file(path);
        _add_log_entry(logType, "Successfully loaded TOML file (" + path + ").");
    } catch (const toml::parse_error& err) {
        logType = required ? RTLogType::ROTEX_LOG_FATAL : RTLogType::ROTEX_LOG_WARNING;
        _add_log_entry(logType, "Failed to parse TOML file (" + path + ") | " + err.description().data() + ".");

        if (required)
            rotex::close();
    }

    return tbl;
}

RTGameData* rotex::_propagate(const toml::table& tbl) {
    auto* gameData = new RTGameData;

    if (tbl.contains("title"))
        gameData->title = *(tbl["title"].value<std::string>());

    if (tbl.contains("width"))
        gameData->width = *(tbl["width"].value<uint32_t>());

    if (tbl.contains("height"))
        gameData->height = *(tbl["height"].value<uint32_t>());

    return gameData;
}
