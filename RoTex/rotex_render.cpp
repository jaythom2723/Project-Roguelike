#include "rotex_render.h"

#include "rotex.h"

RTRenderer::RTRenderer()
{
	hdl = SDL_CreateRenderer(rotex::getContext()->display->getHandle(), nullptr);
	if (hdl == nullptr)
	{
		rotex::pushError(rotex::RTErr::RENDERER_CREATE_ERR);
		return;
	}

	txtHdl = TTF_CreateRendererTextEngine(hdl);
	if (txtHdl == nullptr)
		rotex::pushError(rotex::RTErr::TEXT_ENGINE_CREATE_ERR);
}

RTRenderer::~RTRenderer()
{
	SDL_DestroyRenderer(hdl);
	hdl = nullptr;
}

SDL_Renderer* RTRenderer::getHandle()
{
	return hdl;
}

TTF_TextEngine* RTRenderer::getTextHandle()
{
	return txtHdl;
}
