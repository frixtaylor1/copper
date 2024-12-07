/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#ifndef COLLISIONSYSTEM_HPP
#define COLLISIONSYSTEM_HPP

#include "./ISystem.hpp"

namespace Systems {

class CollisionSystem : public ISystem {
public:
  void update(entt::registry& reg) {
    // MUST_IMPLEMENT();
  }
};

} // namespace Systems

#endif // COLLISIONSYSTEM_HPP
