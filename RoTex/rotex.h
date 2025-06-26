#ifndef ROTEX_H
#define ROTEX_H

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

#include <string>
#include <memory>
#include <stack>

#include "rotex_defs.h"
#include "rotex_err.h"
#include "rotex_display.h"
#include "rotex_render.h"
#include "rotex_loader.h"
#include "rotex_color.h"
#include "rotex_texture.h"
#include "rotex_vec.h"
#include "rotex_event_handler.h"
#include "rotex_grid_map.h"
#include "rotex_entity.h"
#include "rotex_entity_ev.h"
#include "rotex_gui_text.h"
#include "rotex_gui_header.h"

#define RTDISPLAY rotex::getContext()->display
#define RTRENDERER rotex::getContext()->renderer
#define RTMAINFONT rotex::getContext()->font
#define RTENTITIES rotex::getContext()->entityRegistry
#define RTGRIDMAP rotex::getContext()->gridMap
#define RTCURSORMAP rotex::getContext()->cursorMap
#define RTGUIHEADERFONT rotex::getContext()->headerFont
#define RTGUIFONT rotex::getContext()->guiFont

#define RTSIDEBAR_X RTGRIDMAP_WIDTH_PX
#define RTSIDEBAR_WIDTH (RTDISPLAY->getWidth() - RTSIDEBAR_X)
#define RTSIDEBAR_HEIGHT RTDISPLAY->getHeight()

struct RTContext
{
public:
	std::unique_ptr<RTDisplay> display;
	std::unique_ptr<RTRenderer> renderer;
	std::unique_ptr<RTGridMap> gridMap;
	std::unique_ptr<RTGridMap> cursorMap;
	std::vector<std::shared_ptr<RTEntity>> entityRegistry;
	TTF_Font* font;
	TTF_Font* headerFont;
	TTF_Font* guiFont;
};

namespace rotex
{
	ROTEXAPI bool init(const std::string title, const int width, const int height);
	ROTEXAPI void close();
	ROTEXAPI RTContext* getContext();

	// convert a CP437 character to Unicode to UTF8
	ROTEXAPI std::string convertString(uint8_t* cp437_str);

	ROTEXAPI void eventLoop(SDL_Event& e, void(*userDefinedEventLoop)(SDL_Event& e));

	template<typename T>
	bool createEntity(T&& ent)
	{
		RTENTITIES.push_back(std::dynamic_pointer_cast<RTEntity>(ent));
		return true;
	}

	template<typename T, typename... Args>
	std::shared_ptr<T> createEntity(Args&&... args)
	{
		static_assert(std::is_base_of<RTEntity, T>::value, "T must derive RTEntity");

		std::shared_ptr<T> ent = std::make_shared<T>(std::forward<Args>(args)...);
		RTENTITIES.push_back(std::dynamic_pointer_cast<RTEntity>(ent));
		return ent;
	}
}

#endif // ROTEX_H