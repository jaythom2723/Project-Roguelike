//
// Created by pengu on 7/7/2025.
//

#include <iostream>

#include <toml/toml.hpp>

#include "rotex.h"
#include "utility/rotex_data.h"

// private helper functions
bool init_libs(); // initialize all of the external libraries used by rotex
bool init_engine(const std::string& title, const uint32_t width, const uint32_t height); // initialize the internal engine things like RTContext, and more.

namespace rotex {
    // rotex_log.cpp
    extern bool _create_log_file();
    extern void _close_log_file();
    extern void _add_log_entry(const RTLogType, const std::string&);

    // rotex_err.cpp
    extern bool _assert(const bool, RTErrType, const std::string&);
    extern const std::string& _get_error();

    // rotex_loader.cpp
    extern toml::table _parse_toml_file(const std::string&, bool);
    extern RTGameData* _propagate(const toml::table&);
}

// public functions
bool rotex::init() {
    rotex::_create_log_file();
    rotex::_add_log_entry(RTLogType::ROTEX_LOG_INFO, "Log file created.");
    if (!init_libs()) {
        rotex::close();
        return false;
    }
    rotex::_add_log_entry(RTLogType::ROTEX_LOG_INFO, "Engine libraries initialization complete.");

    getContext();

    const RTGameData* gameData = _propagate(_parse_toml_file("data/config/game.toml", true));
    rotex::_add_log_entry(RTLogType::ROTEX_LOG_INFO, "Initializing engine modules.");
    if (!init_engine(gameData->title, gameData->width, gameData->height)) {
        rotex::close();
        delete gameData; // delete before exiting function to prevent leak
        return false;
    }
    delete gameData; // no-longer needed game data

    return true;
}

void rotex::close() {
    _add_log_entry(RTLogType::ROTEX_LOG_INFO, "Game has been closed. Running Cleanup.");
    RTContext* ctx = rotex::getContext();

    if (ctx->display)
        ctx->display.reset(nullptr);

    delete ctx;

    SDL_Quit();
    _close_log_file();
}

// private function implementation
bool init_libs() {
    rotex::_add_log_entry(RTLogType::ROTEX_LOG_INFO, "Attempting to initialize SDL3.");
    // TODO: implement audio with SDL_INIT_AUDIO (unneeded for now)
    if (!rotex::_assert(SDL_Init(SDL_INIT_VIDEO), RTErrType::ROTEX_ENGINE_LIBRARY_INIT_ERROR, "Failed to initialize SDL3")) {
        printf("%s\n", rotex::_get_error().c_str());
        return false;
    }
    rotex::_add_log_entry(RTLogType::ROTEX_LOG_INFO, "Successfully initialized SDL3!");

    rotex::_add_log_entry(RTLogType::ROTEX_LOG_INFO, "Attempting to initialize SDL3_ttf.");
    if (!rotex::_assert(TTF_Init(), RTErrType::ROTEX_ENGINE_LIBRARY_INIT_ERROR, "Failed to initialize SDL3_ttf")) {
        printf("%s\n", rotex::_get_error().c_str());
        return false;
    }
    rotex::_add_log_entry(RTLogType::ROTEX_LOG_INFO, "Successfully initialized SDL3_ttf!");

    return true;
}

bool init_engine(const std::string& title, const uint32_t width, const uint32_t height) {
    rotex::_add_log_entry(RTLogType::ROTEX_LOG_INFO, "Initializing RTDisplay (SDL_Window, SDL_Renderer, TTF_TextEngine).");
    rotex::getContext()->display = std::make_unique<RTDisplay>(title, width, height);
    if (!rotex::_assert(rotex::getContext()->display != nullptr, RTErrType::ROTEX_ENGINE_MODULE_INIT_ERROR, "Failed to initialize the display!")) {
        printf("%s\n", rotex::_get_error().c_str());
        return false;
    }
    rotex::_add_log_entry(RTLogType::ROTEX_LOG_INFO, "Successfully initialized the display!");

    return true;
}
