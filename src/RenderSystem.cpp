/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#include "./RenderSystem.hpp"
#include "AssetsContext.hpp"
#include "Components.hpp"
#include "GameContext.hpp"
#include "LevelManager.hpp"

#include <map>
#include <raylib.h>
#include <terminal.hpp>

namespace Systems {

void RenderSystem::update(entt::registry& reg) {
  BeginDrawing();
    ClearBackground(GameContext::GetBackgroundColor());
      BeginMode2D(GameContext::Player::GetCamera());

      /**
       * Rendering level...
       */
      Services::RenderService::DrawLevel();

      /**
       * Rendering Player...
       * Updating  Camera...
       */
      entt::basic_view playerView = reg.view<Components::Controllable>();
      playerView.each(&Services::RenderService::DrawPlayer);
      playerView.each(&Services::RenderService::DrawCamera);

      EndMode2D();

      /**
       * Rendering Terminal...
       */
      terminalSystem.render();

    DrawFPS(0, 0);
  EndDrawing();
}

  namespace Services {

  void RenderService::DrawPlayer(const Components::Controllable& player) {
    DrawRectangle(
      player.pos.x,
      player.pos.y,
      GameContext::Player::GetSize().x,
      GameContext::Player::GetSize().y, WHITE
    );
  }

  void RenderService::DrawLevel() {
      LevelData level = GameContext::GetLevel();
      size_t row = 0;
      size_t column = 0;

      RenderLevelCtx renderCtx = levelRenderCtx[GameContext::GetLevelIdx()];

      for (size_t cell = 0; cell < level.rows * level.columns; cell++) {
          Vector2 pos = { (float)column * 30, (float)row * 30 };

          Rectangle rectangle = renderCtx.ctx.at(level.ptr[cell]);
          DrawTextureRec(AssetsContext::MapReources::mapTexture, rectangle, pos, WHITE);

          if (++column == level.columns) {
              column = 0;
              row++;
          }
      }
  }

  void RenderService::DrawCamera(const Components::Controllable& player) {
    GameContext::Player::GetCamera().target = { player.pos.x - (float) GetScreenWidth() / 2, player.pos.y - (float) GetScreenHeight() / 2 };
  }



  } // namespace Services

} // namespace Systems

