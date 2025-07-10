//
// Created by pengu on 7/9/2025.
//

#ifndef ROTEX_DATA_STRUCTS_H
#define ROTEX_DATA_STRUCTS_H

#include <string>

extern "C" {
    struct RTGameData {
        std::string title;
        uint32_t width;
        uint32_t height;
    };

    struct RTKeymapData {};
}

#endif //ROTEX_DATA_STRUCTS_H
