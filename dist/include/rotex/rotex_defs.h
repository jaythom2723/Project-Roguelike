//
// Created by pengu on 7/7/2025.
//

#ifndef ROTEX_DEFS_H
#define ROTEX_DEFS_H

#define ROTEX_VERSION_MAJOR 0
#define ROTEX_VERSION_MINOR 0
#define ROTEX_VERSION_PATCH 0

#ifdef ROTEX_EXPORTS
#define ROTEX_API __declspec(dllexport)
#else
#define ROTEX_API __declspec(dllimport)
#endif

// error types
enum RTErrType {
    ROTEX_ENGINE_LIBRARY_INIT_ERROR = 1,
    ROTEX_ENGINE_MODULE_INIT_ERROR,
};

enum RTLogType {
    ROTEX_LOG_INFO = 0,
    ROTEX_LOG_WARNING,
    ROTEX_LOG_ERROR,
    ROTEX_LOG_FATAL
};

#endif //ROTEX_DEFS_H
