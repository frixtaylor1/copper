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
  void update(entt::registry& reg) {
    BeginDrawing();
      ClearBackground(GetColor(0x181818FF));

      entt::basic_view playerView = reg.view<Components::Controllable, Color>();
      playerView.each(&renderPlayer);

      DrawFPS(0, 0);
    EndDrawing();
  }

private:
  static void renderPlayer(const Components::Controllable& movable, const Color& color) {
    DrawRectangle(movable.pos.x, movable.pos.y, 30, 30, color);
  }
};

} // namespace Systems

#endif // RENDERSYSTEM_HPP
