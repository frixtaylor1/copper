/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <raylib.h>

#include "ISystem.hpp"
#include "Components.hpp"

namespace Systems {

class RenderSystem : public ISystem {
public:
  void update(entt::registry& reg);

private:
  static void RenderPlayer(const Components::Controllable& movable, const Color& color);
};

  namespace Services {

  struct RenderService {
    static void DrawPlayer(const Components::Controllable& movable, const Color& color);
  };

  } // namespace Services

} // namespace Systems

#endif // RENDERSYSTEM_HPP
