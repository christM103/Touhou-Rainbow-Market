#pragma once

#include <deque>
#include <tuple>
#include <vector>
#include <memory>
#include <map>

#include <Engine/ECS/System/BaseSystem.hpp>
#include "Engine/Graphics/Sprite.hpp"
#include "Engine/Graphics/Text.hpp"

namespace Engine {
	class RenderSystem {
	public:
		struct RenderBody {
			Entity _ent{};
			RenderComponent* _render{};
			std::vector<std::unique_ptr<Sprite>> _sprite_set{};
			uint16_t _layer{};

			RenderBody(Entity e, RenderComponent* r, std::vector<std::unique_ptr<Sprite>> s) 
				: _ent(e), _render(r), _sprite_set(std::move(s)), _layer(r->_layer_data->layer) {}

			RenderBody() = default;
			RenderBody(const RenderBody&) = delete;
			RenderBody& operator=(const RenderBody&) = delete;
			RenderBody(RenderBody&&) noexcept = default;
			RenderBody& operator=(RenderBody&&) noexcept = default;
		};


		// Constructor and Destructor

		RenderSystem() = default;
		~RenderSystem();

		// Core Functions

		///@brief Loads in eligible entites into the render target queue, updating the text and sprite sets in tandem.
		///@param entityManager The set of entities
		///@param componentManager The set of components that the entity holds
		///@param assetManager The texture manager
		void initRender(ComponentManager* componentManager);

		/// @brief Checks for any collider objects were removed or created
		/// @param entityManager For checking whether entities were removed
		/// @param componentManager For the init of the component manager
		void updateEntities(EntityManager* entityManager, ComponentManager* componentManager);
		
		///@brief Updates the sprite objects within the sprite set
		///@param componentManager The set of components that the entity holds
		///@param assetManager The texture manager
		void updateRender(const ComponentManager* componentManager, const AssetManager* assetManager, const Window* window);

		///@brief Draws all of the sprites currently within the sprite set onto the screen
		///@param assetManager The texture manager for loading the sprites
		///@param window The window that displays the sprites
		void drawRender(const AssetManager* assetManager, const Window* window);

		

		// Overloaded functions

		void create(const SystemContext& ctx);

		void update(const SystemContext& ctx);

		void render(const SystemContext& ctx);

		void quit(const SystemContext& ctx);

	private:
		std::vector<RenderBody> _sprite_set{ }; // Set of multi sprite objects
		CameraComponent* _camera{};
	};

	// Define the Render_Flags enum separately (flags only; no member functions inside enum)
}