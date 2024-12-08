/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#ifndef SOUNDSYSTEM_HPP
#define SOUNDSYSTEM_HPP

#include "ISystem.hpp"

namespace Systems {

class SoundSystem : public ISystem {
public:
  void update(entt::registry& reg) {
    // MUST_IMPLEMENT();
  }
};

} // namespace Systems

#endif // SOUNDSYSTEM_HPP
