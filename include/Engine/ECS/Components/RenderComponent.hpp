#pragma once

#include "Engine/ECS/Components/RenderLayerComponent.hpp"
#include "Engine/ECS/Components/TransformComponent.hpp"
#include "Engine/ECS/Components/SpriteComponent.hpp"
#include "Engine/ECS/Components/TextComponent.hpp"


namespace Engine {
	enum class Render_Flags : uint8_t {
		Null = 0,

		isSingle = 1 << 1,
		isMulti = 1 << 2,

		isSprite = 1 << 3,
		isText = 1 << 4,
	};

	// Bitwise operator helpers for Render_Flags
	inline Render_Flags operator|(Render_Flags a, Render_Flags b) {
		return static_cast<Render_Flags>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
	}
	inline Render_Flags operator&(Render_Flags a, Render_Flags b) {
		return static_cast<Render_Flags>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
	}
	inline Render_Flags operator^(Render_Flags a, Render_Flags b) {
		return static_cast<Render_Flags>(static_cast<uint8_t>(a) ^ static_cast<uint8_t>(b));
	}
	inline Render_Flags operator~(Render_Flags a) {
		return static_cast<Render_Flags>(~static_cast<uint8_t>(a));
	}
	inline Render_Flags& operator|=(Render_Flags& a, Render_Flags b) noexcept {
		a = a | b;
		return a;
	}
	inline Render_Flags& operator&=(Render_Flags& a, Render_Flags b) noexcept {
		a = a & b;
		return a;
	}
	inline Render_Flags& operator^=(Render_Flags& a, Render_Flags b) noexcept {
		a = a ^ b;
		return a;
	}

	struct RenderComponent {
		Render_Flags _flags{ Render_Flags::Null };

		const RenderLayerComponent* _layer_data{ nullptr };
		const TransformComponent* _position_data{ nullptr };
		const SpriteComponent* _sprite_data{ nullptr };
		const TextComponent* _text_data{ nullptr };
		const MultiTransformComponent* _multi_position_data{ nullptr };
		const MultiSpriteComponent* _multi_sprite_data{ nullptr };
		const MultiTextComponent* _multi_text_data{ nullptr };

		RenderComponent(const RenderLayerComponent* l, const TransformComponent* tr, const SpriteComponent* sp = nullptr, const TextComponent* tx = nullptr) 
			: _layer_data(l), _position_data(tr), _sprite_data(sp), _text_data(tx) {
			_flags |= Render_Flags::isSingle;

			if (sp) {
				_flags |= Render_Flags::isSprite;
			} 
			else if (tx) {
				_flags |= Render_Flags::isText;
			}
		}

		RenderComponent(const RenderLayerComponent* l, const MultiTransformComponent* tr, const MultiSpriteComponent* sp = nullptr, const MultiTextComponent* tx = nullptr)
			: _layer_data(l), _multi_position_data(tr), _multi_sprite_data(sp), _multi_text_data(tx) {
			_flags |= Render_Flags::isMulti;

			if (sp) {
				_flags |= Render_Flags::isSprite;
			}
			if (tx) {
				_flags |= Render_Flags::isText;
			}
		}

	};
}