#ifndef ROTEX_ERR_H
#define ROTEX_ERR_H

#include "rotex_defs.h"

#include <string>

namespace rotex
{
	ROTEXAPI const std::string getError();
	ROTEXAPI void pushError(RTErr code);
	ROTEXAPI bool pushErrRet(RTErr code);
}

#endif // ROTEX_ERR_H