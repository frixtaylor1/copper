/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#ifndef COLLISIONSYSTEM_HPP
#define COLLISIONSYSTEM_HPP

#include "ISystem.hpp"
#include "Components.hpp"
#include <raylib.h>

namespace Systems {

class CollisionSystem : public ISystem {
public:
  void update(entt::registry& reg);
};

  namespace Services {

  struct CollisionService {
      static bool PlayerCollides(const Components::Controllable& player, const Vector2& direction);
  };

  }// namespace Services

} // namespace Systems

#endif // COLLISIONSYSTEM_HPP
