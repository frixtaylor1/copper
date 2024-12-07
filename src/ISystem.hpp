/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#ifndef ISYSTEM_HPP
#define ISYSTEM_HPP

#include <entt.hpp>

namespace Systems {

struct ISystem {
  virtual ~ISystem() {}
  virtual void update(entt::registry& reg) = 0;
};

} // namespace Systems

#endif // ISYSTEM_HPP
