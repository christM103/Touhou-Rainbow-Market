#pragma once

#include "Engine/ECS/System/Systems.hpp"
#include "Engine/ECS/ComponentManager.hpp"

namespace Engine {

	class SystemManager {
	
	public:
		SystemManager() = default;
		~SystemManager() = default;

		void init() {
		}

		template<typename SystemType>
		void addSystem(std::unique_ptr<SystemType> system) {
			System sysType = std::type_index(typeid(SystemType));
			if (activeSystems.find(sysType) == activeSystems.end()) {
				systems.push_back(std::make_unique<SystemData<SystemType>>(std::move(system)));
				activeSystems.try_emplace(sysType, true);
			}
			else {
				std::cerr << "System already exists" << std::endl;
			}
		}

		template<typename SystemType>
		void addSystem() {
			this->addSystem(std::make_unique<SystemType>());
		}

		template<typename SystemType>
		void toggleSystem(bool isRunning) {
			System system = std::type_index(typeid(SystemType));
			activeSystems.find(system)->second = isRunning;
		}

		template<typename SystemType>
		bool isSystemRunning() {
			System system = std::type_index(typeid(SystemType));
			return (activeSystems.find(system)->second);
		}

		template<typename SystemType>
		void initSystem() {
			System system = std::type_index(typeid(SystemType));
			auto index = activeSystems.find(system);
			if (index != activeSystems.end()) {
				auto& currentSystem = systems[std::distance(activeSystems.begin(), index)];
				currentSystem->create(ctx);
			}
		}

		void create() {
			for (auto& sys : systems) {
				sys->create(ctx);
			}
		}

		void update() {
			for (auto& sys : systems) {
				sys->update(ctx);
			}
		}

		void render() {
			for (auto& sys : systems) {
				sys->render(ctx);
			}
		}

		void quit() {
			for (auto& sys : systems) {
				sys->quit(ctx);
				sys.release();
			}
			activeSystems.clear();
			systems.clear();
		}

		template<typename Manager>
		void setManager(const std::unique_ptr<Manager>& manager) {
			setManager(manager.get());
		}

		template<typename Manager>
		void setManager(Manager* manager) {

			if constexpr (std::is_same_v<Manager, EntityManager>) {
				ctx.entityManager = manager;
			}
			else if constexpr (std::is_same_v<Manager, ComponentManager>) {
				ctx.componentManager = manager;
			}
			else if constexpr (std::is_same_v<Manager, AssetManager>) {
				ctx.assetManager = manager;
			}
			else if constexpr (std::is_same_v<Manager, Input>) {
				ctx.input = manager;
			}
			else if constexpr (std::is_same_v<Manager, Window>) {
				ctx.window = manager;
			}
			else {
				static_assert(false, "setManager: unsupported manager type");
			}
		}



	private:
		/// Virtual system functions shared within all system files

		class SystemFunction {
		public:
			virtual void create(const SystemContext& ctx) = 0;
			virtual void update(const SystemContext& ctx) = 0;
			virtual void render(const SystemContext& ctx) = 0;
			virtual void quit(const SystemContext& ctx) = 0;
			virtual ~SystemFunction() = default;
		};

		template<typename SystemType>
		class SystemData : public SystemFunction {
		public:
			explicit SystemData(std::unique_ptr<SystemType> sys) : systemPtr(std::move(sys)) {}

			void create(const SystemContext& ctx) override { systemPtr->create(ctx); }
			void update(const SystemContext& ctx) override { systemPtr->update(ctx); }
			void render(const SystemContext& ctx) override { systemPtr->render(ctx); }
			void quit(const SystemContext& ctx) override { systemPtr->quit(ctx); }

		private:
			std::unique_ptr<SystemType> systemPtr;
		};

		std::vector<std::unique_ptr<SystemFunction>> systems;
		std::unordered_map<System, bool> activeSystems;
		SystemContext ctx;

	};

}