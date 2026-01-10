#include "Engine/Graphics/Text.hpp"

Engine::Text::Text(const char* string) : _text_string(string) {
	_text_font = TTF_OpenFont("assets/fonts/ArialMdm.ttf", _text_size);
}

Engine::Text::Text(const char* string, int size) : _text_string(string), _text_size(size) {
	_text_font = TTF_OpenFont("assets/fonts/ArialMdm.ttf", size);
}

Engine::Text::Text(const char* file, char* string, int size) : _text_string(string), _text_size(size) {
	_text_font = TTF_OpenFont(file, size);
}

Engine::Text::~Text() {
	if (_texture) {
		SDL_DestroyTexture(_texture);
	}
	if (_text_font) {
		TTF_CloseFont(_text_font);
	}
}

SDL_Texture* Engine::Text::load(SDL_Renderer* renderer, Recti text_space)
{
	// Setting text dimensions
	_texture_space = { text_space.position.x, text_space.position.y, text_space.size.x, text_space.size.y };

	// Setting text color
	SDL_Color color = _text_color;

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

	// Applying attribute data to fonts
	TTF_SetFontStyle(_text_font, renderstyle);
	TTF_SetFontKerning(_text_font, 1);
	TTF_SetFontSize(_text_font, _text_size);

	// Creating the texture
	SDL_Surface* text = TTF_RenderText_Solid_Wrapped(_text_font, _text_string.c_str(), color, text_space.size.x);
	if (_texture) {
		SDL_DestroyTexture(_texture);
	}
	_texture = SDL_CreateTextureFromSurface(renderer, text);
	SDL_FreeSurface(text);
	SDL_QueryTexture(_texture, NULL, NULL, &_texture_space.size.x, &_texture_space.size.y);
	return _texture;

}

SDL_Texture* Engine::Text::load(SDL_Renderer* renderer, Vector2i pos, Vector2i size)
{
	return load(renderer, Recti(pos, size));
}

SDL_Texture* Engine::Text::load(SDL_Renderer* renderer, int x, int y, int width, int height)
{
	return load(renderer, Recti(x, y, width, height));
}
