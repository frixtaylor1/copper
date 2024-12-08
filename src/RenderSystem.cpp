/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#include "./RenderSystem.hpp"

namespace Systems {

void RenderSystem::update(entt::registry& reg) {
  BeginDrawing();
    ClearBackground(GetColor(0x181818FF));

    entt::basic_view playerView = reg.view<Components::Controllable, Color>();
    playerView.each(&RenderPlayer);

    DrawFPS(0, 0);
  EndDrawing();
}

void RenderSystem::RenderPlayer(const Components::Controllable& movable, const Color& color) {
  Services::RenderService::DrawPlayer(movable, color);
}

  namespace Services {

  void RenderService::DrawPlayer(const Components::Controllable& movable, const Color& color) {
    DrawRectangle(movable.pos.x, movable.pos.y, 30, 30, color);
  }

  } // namespace Services

} // namespace Systems

