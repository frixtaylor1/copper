/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#ifndef SYSTEMMANAGER_HPP
#define SYSTEMMANAGER_HPP

#include "./ControlSystem.hpp"
#include "./RenderSystem.hpp"
#include "./CollisionSystem.hpp"
#include "./SoundSystem.hpp"
#include "./PhysicsSystem.hpp"

namespace Managers {

class SystemManager {
public:
  SystemManager() = default;

  void updateSystems(entt::registry& reg) {
    for (Systems::ISystem* system : systems) {
      system->update(reg);
    }
  }

private:
  ::Systems::RenderSystem    renderSystem;
  ::Systems::PhysicsSystem   physicsSystem;
  ::Systems::ControlSystem   movementSystem;
  ::Systems::CollisionSystem collisionSystem;
  ::Systems::SoundSystem     soundSystem;

private:
  Systems::ISystem* systems[5] = {
    &renderSystem,
    &movementSystem,
    &physicsSystem,
    &collisionSystem,
    &soundSystem
  };
};

};

#endif // SYSTEMMANAGER_HPP
