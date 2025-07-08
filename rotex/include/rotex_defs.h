//
// Created by pengu on 7/7/2025.
//

#ifndef ROTEX_DEFS_H
#define ROTEX_DEFS_H

#ifdef ROTEX_EXPORTS
#define ROTEX_API __declspec(dllexport)
#else
#define ROTEX_API __declspec(dllimport)
#endif

#endif //ROTEX_DEFS_H
