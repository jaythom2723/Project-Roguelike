#include "rotex_gui_text.h"

#include "rotex.h"

RTGUIText::RTGUIText(TTF_Font* font, std::vector<std::string> texts, std::vector<RTColor> colors)
{
	int i;
	for (i = 0; i < texts.size(); i++)
	{
		textures.push_back(new RTTexture(font, texts[i], colors[i]));
		if (textures[i] == nullptr)
		{
			std::printf("Could not generate a texture for a gui header!\n");
			std::exit(-5);
		}
	}
}

RTGUIText::~RTGUIText()
{
	for (auto tex : textures)
	{
		if (tex == nullptr)
			break;

		delete tex;
	}
}

void RTGUIText::setNewTextAt(TTF_Font* font, std::string text, RTColor color, int index)
{
	if (textures[index] != nullptr) // don't try to delete something that doesn't already exist
		delete textures[index];
	textures[index] = new RTTexture(font, text, color); // allocate a new texture to be made at `index`
}

std::vector<RTTexture*> RTGUIText::getTextures()
{
	return textures;
}

RTTexture* RTGUIText::getTextureAt(int i)
{
	return textures[i];
}

// get the sum of all the widths in the textures array and return it
float RTGUIText::getWidth()
{
	float ret = 0.f;

	for (auto tex : textures) 
	{
		if (tex == nullptr) // if we hit a nullptr, break the loop
			break;

		ret += tex->getWidth();
	}

	return ret;
}

float RTGUIText::getHeight()
{
	if (textures[0] == nullptr) // if the first element is nullptr, return -1
		return -1.f;

	return textures[0]->getHeight(); // only need the height of the first element
}

void RTGUIText::draw(RTVec2<float> pos)
{
	int i;
	float x = pos.x;
	for (i = 0; i < textures.size(); i++)
	{
		if (i > 0)
			x += textures[i - 1]->getWidth(); // x offsets by the previous texture's width after 0th index

		SDL_FRect rect = {};
		rect.x = x;
		rect.y = pos.y;
		rect.w = textures[i]->getWidth();
		rect.h = textures[i]->getHeight();

		SDL_RenderTexture(RTRENDERER->getHandle(), textures[i]->getRaw(), nullptr, &rect);

		// TODO: remove the debug dots
		SDL_SetRenderDrawColor(RTRENDERER->getHandle(), 0xff, 0x00, 0x00, 0xff);
		SDL_RenderPoint(RTRENDERER->getHandle(), x, pos.y);
		SDL_SetRenderDrawColor(RTRENDERER->getHandle(), 0x00, 0x00, 0x00, 0xff);
	}
}