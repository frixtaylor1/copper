/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <raylib.h>

#include "AssetsContext.hpp"
#include "GameContext.hpp"
#include "ISystem.hpp"
#include "Components.hpp"

namespace Systems {

class RenderSystem : public ISystem {
public:
  void update(entt::registry& reg);
};

  namespace Services {

  struct RenderService {
    static void DrawPlayer(const Components::Controllable& player);
    static void DrawLevel();
    static void DrawCamera(const Components::Controllable& player);
  };

  } // namespace Services

} // namespace Systems

#endif // RENDERSYSTEM_HPP
