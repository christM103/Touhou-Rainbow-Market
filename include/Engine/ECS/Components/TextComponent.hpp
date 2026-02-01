#pragma once

#include <string>
#include <unordered_map>

#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/Vector4.hpp"

namespace Engine {
	class TextComponent{
	public:
		TextComponent() : text(""), textSize(0), textColor( 0, 0, 0, 0 ) {}
		~TextComponent() = default;

		TextComponent(const char* tx, int txsz, const Vector4<int> tcol) : text(tx), textSize(txsz), textColor(tcol) {}

		// Mutators and Accessors

		const char* const getText() const { return text.c_str(); }
		const int getTextSize() const { return textSize; }
		const Vector4i getTextColor() const { return textColor; }

		void setText(const char* str) { text = str; }
		void setTextSize(int size) { textSize = size; }
		void setTextColor(Vector4i txtC) { textColor = txtC; }

		// Comparison operators

		bool operator==(const TextComponent& r2) const {
			return ((text.compare(r2.getText()) == 0) && (getTextSize() == r2.getTextSize()) && (getTextColor() == r2.getTextColor()));
		}
		bool operator!=(const TextComponent& r2) const {
			return !(*this == r2);
		}

	private:

		std::string text; // Text of the TextComponent

		int textSize; // Size of the text

		Vector4i textColor; //  Bounds of the text (When set to 0 on default, width has no bounds)

	};

	struct MultiTextComponent {
		std::unordered_map<uint8_t, TextComponent*> text;
	};
}