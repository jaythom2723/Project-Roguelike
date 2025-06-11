#include "rotex_loader.h"

#include "rotex_err.h"

TTF_Font* rotex::loadFont(std::string path, float pt_size)
{
	TTF_Font* ret = TTF_OpenFont(path.c_str(), pt_size);
	if (ret == nullptr)
	{
		rotex::pushError(rotex::RTErr::ASSET_LOAD_FAILURE_ERR);
		return nullptr;
	}

	return ret;
}