#pragma once

#include <SDL2/SDL_ttf.h>
#include <string>

#include "Engine/Graphics/Sprite.hpp"
#include "Engine/Math/Vector4.hpp"

namespace Engine {
	class Text : public Sprite {
	public:
		enum Text_Attr : Uint16 {
			Null = 0,
			Caps = 1 << 0,
			Bold = 1 << 1,
			Italics = 1 << 2,
			Underline = 1 << 3,
			Strikethrough = 1 << 4,
			Centered = 1 << 5,

		};

		Text(const char* string);
		Text(const char* string, int size);
		Text(const char* file, const char* string, int size);
		Text(int width, int height, const char* string, int size);
		~Text();

		bool load(SDL_Renderer* renderer, std::string texture_name, const AssetManager* manager, Recti text_space);
		bool load(SDL_Renderer* renderer, std::string texture_name, const AssetManager* manager, Vector2i pos, Vector2i size);
		bool load(SDL_Renderer* renderer, std::string texture_name, const AssetManager* manager, int x, int y, int width, int height);
		bool load(SDL_Renderer* renderer, std::string texture_name, const AssetManager* manager);

		// Text Specific Functions
		inline void setText(const char* text) { _text_string = text; }
		inline void setTextSize(int size) { _text_size = size; }
		inline void setAttr(Text_Attr attr) { _text_attr ^= attr; }
		inline void remAttr(Text_Attr attr) { _text_attr ^= ~attr; }
		inline void setColor(Vector4i col) { _text_color = col; }
		inline void setFont(TTF_Font* font) { _text_font = font; }
		inline void setTextBounds(Vector2i bounds) { _text_bounds = bounds; }

		inline const char* getText() { return _text_string.c_str(); }
		inline int getTextSize() { return _text_size; }
		inline Uint16 getTextAttr() { return _text_attr; }
		inline Vector4i getTextColor() { return _text_color; }
		inline TTF_Font* getFont() { return _text_font; }
		inline Vector2i getTextBounds() { return _text_bounds; }

		// Overloaded Functions

		inline bool checkAttr(Text_Attr attr) { return _text_attr & attr; }

	private:
		std::string _text_string{ "" };
		int _text_size{ 10 };
		Uint16 _text_attr{ Null };
		Vector2i _text_bounds{ 0,0 };
		Vector4i _text_color{ 255, 255, 255, 255 };
		TTF_Font* _text_font;
	};
}