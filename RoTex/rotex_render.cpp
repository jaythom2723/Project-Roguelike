#include "rotex_render.h"

#include "rotex.h"

RTRenderer::RTRenderer()
{
	hdl = SDL_CreateRenderer(rotex::getContext()->display->getHandle(), nullptr); // create the SDL3 renderer
	if (hdl == nullptr) // if nullptr, push RENDERER_CREATE_ERR to the error stack, return
	{
		rotex::pushError(rotex::RTErr::RENDERER_CREATE_ERR);
		return;
	}

	txtHdl = TTF_CreateRendererTextEngine(hdl); // create the text engine from a renderer context
	if (txtHdl == nullptr) // if nullptr, push TEXT_ENGINE_CREATE_ERR to the error stack
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
