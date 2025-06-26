#include "rotex.h"

#include "rotex_defs.h"
#include "rotex_err.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>

// used in conjunction with rotex::convertString
// lookup table containing 16-bit unicode characters for CP437 to Unicode conversion
static const uint16_t cp437_to_unicode[256] = {
	0x0000, 0x263A, 0x263B, 0x2665, 0x2666, 0x2663, 0x2660, 0x2022,
	0x25D8, 0x25CB, 0x25D9, 0x2642, 0x2640, 0x266A, 0x266B, 0x263C,
	0x25BA, 0x25C4, 0x2195, 0x203C, 0x00B6, 0x00A7, 0x25AC, 0x21A8,
	0x2191, 0x2193, 0x2192, 0x2190, 0x221F, 0x2194, 0x25B2, 0x25BC,
	0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027,
	0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F,
	0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037,
	0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F,
	0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047,
	0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F,
	0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057,
	0x0058, 0x0059, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F,
	0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067,
	0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F,
	0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077,
	0x0078, 0x0079, 0x007A, 0x007B, 0x007C, 0x007D, 0x007E, 0x2302,
	0x00C7, 0x00FC, 0x00E9, 0x00E2, 0x00E4, 0x00E0, 0x00E5, 0x00E7,
	0x00EA, 0x00EB, 0x00E8, 0x00EF, 0x00EE, 0x00EC, 0x00C4, 0x00C5,
	0x00C9, 0x00E6, 0x00C6, 0x00F4, 0x00F6, 0x00F2, 0x00FB, 0x00F9,
	0x00FF, 0x00D6, 0x00DC, 0x00A2, 0x00A3, 0x00A5, 0x20A7, 0x0192,
	0x00E1, 0x00ED, 0x00F3, 0x00FA, 0x00F1, 0x00D1, 0x00AA, 0x00BA,
	0x00BF, 0x2310, 0x00AC, 0x00BD, 0x00BC, 0x00A1, 0x00AB, 0x00BB,
	0x2591, 0x2592, 0x2593, 0x2502, 0x2524, 0x2561, 0x2562, 0x2556,
	0x2555, 0x2563, 0x2551, 0x2557, 0x255D, 0x255C, 0x255B, 0x2510,
	0x2514, 0x2534, 0x252C, 0x251C, 0x2500, 0x253C, 0x255E, 0x255F,
	0x255A, 0x2554, 0x2569, 0x2566, 0x2560, 0x2550, 0x256C, 0x2567,
	0x2568, 0x2564, 0x2565, 0x2559, 0x2558, 0x2552, 0x2553, 0x256B,
	0x256A, 0x2518, 0x250C, 0x2588, 0x2584, 0x258C, 0x2590, 0x2580,
	0x03B1, 0x00DF, 0x0393, 0x03C0, 0x03A3, 0x03C3, 0x00B5, 0x03C4,
	0x03A6, 0x0398, 0x03A9, 0x03B4, 0x221E, 0x03C6, 0x03B5, 0x2229,
	0x2261, 0x00B1, 0x2265, 0x2264, 0x2320, 0x2321, 0x00F7, 0x2248,
	0x00B0, 0x2219, 0x00B7, 0x221A, 0x207F, 0x00B2, 0x25A0, 0x00A0
};

// encodes a single 16-bit unicode character into an 8-bit utf-8 character
// stores the result in char* out, returns number of bytes in the new string.
int encode_utf8(uint32_t codepoint, char* out)
{
	if (codepoint <= 0x7F)
	{
		(*out) = codepoint;
		return 1;
	}
	else if (codepoint <= 0x7FF)
	{
		(*out) = 0xc0 | (codepoint >> 6);
		*(out + 1) = 0x80 | (codepoint & 0x3f);
		return 2;
	}
	else if (codepoint <= 0xFFFF)
	{
		(*out) = 0xe0 | (codepoint >> 12);
		*(out + 1) = 0x80 | ((codepoint >> 6) & 0x3f);
		*(out + 2) = 0x80 | (codepoint & 0x3f);
		return 3;
	}

	return 0; // unsupported
}

// convert a cp437 encoded string into a utf8 encoded string
char* cp437_to_utf8_string(const uint8_t* input)
{
	using namespace std;
	size_t len = strlen((const char*)input);
	char* utf8 = (char*)malloc(len * 4 + 1);
	if (utf8 == nullptr) // if we can't allocate memory, quit.
	{
		std::printf("Could not allocate enough memory for conversion!\n");
		std::exit(-4);
	}

	// create a temp variable so we don't have to worry about resetting the utf8 pointer
	char* out = utf8;

	for (size_t i = 0; i < len; ++i)
	{
		uint16_t unicode = cp437_to_unicode[input[i]]; // get the associated 16-bit Unicode character
		int bytes = encode_utf8(unicode, out); // encode it into utf-8, returns size in bytes
		out += bytes; // move over N bytes
	}

	*out = '\0';
	return utf8;
}

RTContext* ctx = nullptr;

bool rotex::init(const std::string title, const int w, const int h)
{
	// initialize SDL3
	if (!SDL_Init(SDL_INIT_VIDEO))
		return rotex::pushErrRet(rotex::RTErr::SDL_INIT_ERR);
	
	// initialize the whole context
	// TODO: refactor for "new"
	ctx = (RTContext*) std::calloc(1, sizeof(RTContext));
	if (ctx == nullptr)
		return rotex::pushErrRet(rotex::RTErr::MEM_ALLOC_ERR);

	// initialize the display
	ctx->display = std::make_unique<RTDisplay>(title, w, h);
	if (ctx->display->getHandle() == nullptr)
		return false;
	
	// initialize the renderer
	ctx->renderer = std::make_unique<RTRenderer>();
	if (ctx->renderer->getHandle() == nullptr)
		return false;
	if (ctx->renderer->getTextHandle() == nullptr)
		return rotex::pushErrRet(rotex::RTErr::RENDERER_CREATE_ERR);

	// initialize the grid map
	ctx->gridMap = std::make_unique<RTGridMap>();
	if (ctx->gridMap == nullptr)
		return rotex::pushErrRet(rotex::RTErr::GRIDMAP_CREATE_ERR);

	ctx->cursorMap = std::make_unique<RTGridMap>();
	if (ctx->cursorMap == nullptr)
		return rotex::pushErrRet(rotex::RTErr::GRIDMAP_CREATE_ERR);

	// initialize SDL3_ttf
	if (!TTF_Init())
		return rotex::pushErrRet(rotex::RTErr::TTF_INIT_ERR);

	// initialize the main font
	ctx->font = rotex::loadFont("gfx/fonts/Mx437_IBM_BIOS.ttf", 16.f);
	if (ctx->font == nullptr)
	{
		std::printf("%s > mainFont is NULL!\n", rotex::getError().c_str());
		return false;
	}

	// initialize the header font
	ctx->headerFont = rotex::loadFont("gfx/fonts/Mx437_Robotron_A7100.ttf", 32.f);
	if (ctx->headerFont == nullptr)
	{
		std::printf("%s > headerFont is NULL!\n", rotex::getError().c_str());
		return false;
	}

	// initialize the GUI font
	ctx->guiFont = rotex::loadFont("gfx/fonts/Mx437_Robotron_A7100.ttf", 16.f);
	if (ctx->guiFont == nullptr)
	{
		std::printf("%s > guiFont is NULL!\n", rotex::getError().c_str());
		return false;
	}

	return true;
}

void rotex::close()
{
	// if the context is already destroyed or uninitialized, do nothing
	if (ctx == nullptr)
		return;

	// destroy all of the loaded fonts
	TTF_CloseFont(ctx->font);
	TTF_CloseFont(ctx->headerFont);
	TTF_CloseFont(ctx->guiFont);

	// free the context
	// TODO: refactor for delete
	std::free(reinterpret_cast<void*>(ctx));
	ctx = nullptr;

	SDL_Quit();
}

RTContext* rotex::getContext()
{
	return ctx;
}

// convert a string from CP437 encoding to UTF-8 encoding.
std::string rotex::convertString(uint8_t* cp437_str)
{
	char* tmp = cp437_to_utf8_string(cp437_str);
	std::string ret = tmp;
	free((void*)tmp);
	tmp = nullptr;
	return ret;
}

void rotex::eventLoop(SDL_Event& e, void(*userDefinedEventLoop)(SDL_Event& e))
{
	int i = 0;

	while (SDL_PollEvent(&e))
	{
		// end the application if SDL_EVENT_QUIT
		if (e.type == SDL_EVENT_QUIT)
		{
			RTDISPLAY->setClose(true);
			return;
		}

		// push a new event to the RTEntityEV's
		for (i = 0; i < RTENTITIES.size(); i++)
		{
			std::shared_ptr<RTEntityEV> ent = std::dynamic_pointer_cast<RTEntityEV>(RTENTITIES[i]);
			if (ent.get() == nullptr)
				continue; // move to the next entity if cannot convert to RTEntityEV

			rotex::RTEvent event = {};
			event.type = (SDL_EventType)e.type;

			RTEventHandler* handler = ent->getEventHandler();

			// TODO: make this its own function?
			switch (e.type)
			{
			case SDL_EVENT_KEY_DOWN:
				event.code = e.key.scancode;
				break;
			}

			// only push if the mask equals the same type of event
			if (handler->getMask() == e.type)
				handler->pushEvent(event);
		}

		// call the user defined event loop, if necessary
		if (userDefinedEventLoop != nullptr)
			(*userDefinedEventLoop)(e);
	}
}