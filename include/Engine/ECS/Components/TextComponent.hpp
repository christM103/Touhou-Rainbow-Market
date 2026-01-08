#pragma once

#include <string>

namespace Engine {
	class TextComponent : public SpriteComponent {
	public:
		TextComponent() : SpriteComponent(), text(""), textsize(0) {}
		~TextComponent() = default;

		TextComponent(const Rect<float>& rect, const Vector2<float>& off, const char& tx, int txsz) :
			SpriteComponent(rect, off), text(tx), textsize(txsz) {}
	private:
		std::string_view text;
		int textsize;
	};
}