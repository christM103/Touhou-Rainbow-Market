#pragma once

#include <deque>

#include <Engine/ECS/System/BaseSystem.hpp>
#include "Engine/Graphics/Sprite.hpp"
#include "Engine/Graphics/Text.hpp"

namespace Engine {
	class RenderSystem {

	using isSprite = std::true_type;
	using isText = std::false_type;
	using RenderTarget = std::tuple<Entity, bool, uint16_t>;

	public:
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
		std::unordered_map<Entity, std::unique_ptr<Sprite>> _sprite_set{ }; // Set of Sprite Objects
		std::unordered_map<Entity, std::unique_ptr<Text>> _text_set{ }; // Set of Text Objects
	};
}