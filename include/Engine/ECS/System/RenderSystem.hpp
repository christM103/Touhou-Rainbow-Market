#pragma once

#include <deque>
#include <tuple>
#include <vector>
#include <memory>
#include <unordered_map>

#include <Engine/ECS/System/BaseSystem.hpp>
#include "Engine/Graphics/Sprite.hpp"
#include "Engine/Graphics/Text.hpp"

namespace Engine {
	class RenderSystem {
	public:
		enum class Render_Flags : uint8_t {
			Null = 0,

			isSingle = 1 << 1,
			isMulti = 1 << 2,

			isSprite = 1 << 3,
			isText = 1 << 4,
		};

		// Bitwise operator helpers for Render_Flags
		friend constexpr Render_Flags operator|(Render_Flags a, Render_Flags b) noexcept {
			return static_cast<Render_Flags>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
		}
		friend constexpr Render_Flags operator&(Render_Flags a, Render_Flags b) noexcept {
			return static_cast<Render_Flags>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
		}
		friend constexpr Render_Flags operator^(Render_Flags a, Render_Flags b) noexcept {
			return static_cast<Render_Flags>(static_cast<uint8_t>(a) ^ static_cast<uint8_t>(b));
		}
		friend constexpr Render_Flags operator~(Render_Flags a) noexcept {
			return static_cast<Render_Flags>(~static_cast<uint8_t>(a));
		}
		friend Render_Flags& operator|=(Render_Flags& a, Render_Flags b) noexcept {
			a = a | b;
			return a;
		}
		friend Render_Flags& operator&=(Render_Flags& a, Render_Flags b) noexcept {
			a = a & b;
			return a;
		}
		friend Render_Flags& operator^=(Render_Flags& a, Render_Flags b) noexcept {
			a = a ^ b;
			return a;
		}

		// Alias for render target tuple
		using RenderTarget = std::tuple<Entity, Render_Flags, uint16_t>;


		// Constructor and Destructor

		RenderSystem() = default;
		~RenderSystem();

		// Core Functions

		///@brief Loads in eligible entites into the render target queue, updating the text and sprite sets in tandem.
		///@param entityManager The set of entities
		///@param componentManager The set of components that the entity holds
		///@param assetManager The texture manager
		void init(const EntityManager* entityManager, const ComponentManager* componentManager,
			const AssetManager* assetManager, const Window* window);
		
		void draw(const EntityManager* entityManager, const ComponentManager* componentManager,
			const AssetManager* assetManager, const Window* window);

		void update(const EntityManager* entityManager, const ComponentManager* componentManager,
			const AssetManager* assetManager, const Window* window);

		// Overloaded functions

		void create(const SystemContext& ctx);

		void update(const SystemContext& ctx);

		void render(const SystemContext& ctx);

		void quit(const SystemContext& ctx);

	private:
		std::deque<RenderTarget> _render_targets{ }; // Set of renderable entities
		std::unordered_map<Entity, std::vector<std::unique_ptr<Sprite>>> _sprite_set{ }; // Set of multi sprite objects
	};

	// Define the Render_Flags enum separately (flags only; no member functions inside enum)
}