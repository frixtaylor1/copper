/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSYSTEM_HPP

#include "./ISystem.hpp"

namespace Systems {
  
class PhysicsSystem : public ISystem {
public:
  void update(entt::registry& reg) {
    // MUST_IMPLEMENT();
  }
};

} // namespace Systems

#endif // PHYSICSSYSTEM
