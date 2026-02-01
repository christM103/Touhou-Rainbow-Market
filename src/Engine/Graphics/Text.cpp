#include "Engine/Graphics/Text.hpp"

Engine::Text::Text(const char* string) : Sprite(), _text_string(string) {
	_text_font = TTF_OpenFont("assets/fonts/ArialMdm.ttf", _text_size);
}

Engine::Text::Text(const char* string, int size) : Sprite(), _text_string(string), _text_size(size) {
	_text_font = TTF_OpenFont("assets/fonts/ArialMdm.ttf", size);
}

Engine::Text::Text(int width, int height, const char* string, int size) : Sprite(width, height), _text_string(string), _text_size(size) {
	_text_font = TTF_OpenFont("assets/fonts/ArialMdm.ttf", size);
}

Engine::Text::Text(const char* file, char* string, int size) : Sprite(), _text_string(string), _text_size(size) {
	_text_font = TTF_OpenFont(file, size);
}

Engine::Text::~Text() {
	if (_text_font) {
		TTF_CloseFont(_text_font);
	}
}

bool Engine::Text::load(SDL_Renderer* renderer, std::string texture_name, const AssetManager* manager, Recti text_space)
{
	// Setting text dimensions
	_dest_rect = text_space;

	// Setting text color
	SDL_Color color = { static_cast<Uint8>(_text_color.w), static_cast<Uint8>(_text_color.x), 
		static_cast<Uint8>(_text_color.y), static_cast<Uint8>(_text_color.z) };

	// Setting attributes
	if (checkAttr(Caps)) {
		for (char& c : _text_string) {
			c = std::toupper(c);
		}
	}
	int renderstyle = TTF_STYLE_NORMAL;
	if (checkAttr(Bold)) { renderstyle |= TTF_STYLE_BOLD; }
	if (checkAttr(Italics)) { renderstyle |= TTF_STYLE_ITALIC; }
	if (checkAttr(Underline)) { renderstyle |= TTF_STYLE_UNDERLINE; }
	if (checkAttr(Strikethrough)) { renderstyle |= TTF_STYLE_STRIKETHROUGH; }
	if (checkAttr(Centered)) { TTF_SetFontWrappedAlign(_text_font, TTF_WRAPPED_ALIGN_CENTER); }

	// Applying attribute data to fonts
	TTF_SetFontStyle(_text_font, renderstyle);
	TTF_SetFontKerning(_text_font, 1);
	TTF_SetFontSize(_text_font, _text_size);

	// Creating the texture
	SDL_Surface* text = TTF_RenderText_Solid_Wrapped(_text_font, _text_string.c_str(), color, _text_bounds.x);
	if (manager->getTexture(_textureID.c_str())) {
		const_cast<AssetManager*>(manager)->destroyTexture(_textureID.c_str());
	}
	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text);
	SDL_FreeSurface(text);
	SDL_QueryTexture(text_texture, NULL, NULL, &_text_bounds.x, &_text_bounds.y);
	_dest_rect.size = _text_bounds;
	_src_rect.size = _dest_rect.size;

	const_cast<AssetManager*>(manager)->storeTexture(text_texture, texture_name.c_str(), renderer);
	_textureID = texture_name;

	return true;

}

bool Engine::Text::load(SDL_Renderer* renderer, std::string texture_name, const AssetManager* manager)
{
	return load(renderer, texture_name, manager, Recti(0, 0, 0, 0));
}

bool Engine::Text::load(SDL_Renderer* renderer, std::string texture_name, const AssetManager* manager, Vector2i pos, Vector2i size)
{
	return load(renderer, texture_name, manager, Recti(pos, size));
}

bool Engine::Text::load(SDL_Renderer* renderer, std::string texture_name, const AssetManager* manager, int x, int y, int width, int height)
{
	return load(renderer, texture_name, manager, Recti(x, y, width, height));
}
