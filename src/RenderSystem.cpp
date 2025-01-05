/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#include "./RenderSystem.hpp"
#include "AssetsContext.hpp"
#include "Components.hpp"
#include "GameContext.hpp"

#include <raylib.h>
#include <terminal.hpp>

namespace Systems {

void RenderSystem::update(entt::registry& reg) {
  BeginDrawing();
    ClearBackground(GetColor(0x181818FF));
      BeginMode2D(GameContext::Player::camera2d);

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
      terminalSystem.update(reg);

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
    size_t row      = 0;
    size_t column   = 0;


    for (size_t cell = 0; cell < level.rows * level.columns; cell++) {
      Vector2 pos = { (float) column * 30, (float) row * 30 };
      switch (level.ptr[cell]) {
        case 1:
          DrawTextureRec(
            AssetsContext::MapReources::mapTexture,
            AssetsContext::MapReources::GetMountainWallRectangle(),
            pos,
            WHITE
          );
          break;
        case 2:
          DrawTextureRec(
            AssetsContext::MapReources::mapTexture,
            AssetsContext::MapReources::GetDoorRectangle(),
            pos,
            WHITE
          );
          break;
        case 10:
          DrawTextureRec(
            AssetsContext::MapReources::mapTexture,
            AssetsContext::MapReources::GetGreenGrassGroundRectangle(),
            pos,
            WHITE
          );
          break;
        case 11:
          DrawTextureRec(
            AssetsContext::MapReources::mapTexture,
            AssetsContext::MapReources::GetYellowGrassGroundLeftRectangle(),
            pos,
            WHITE
          );
          break;
        case 12:
          DrawTextureRec(
            AssetsContext::MapReources::mapTexture,
            AssetsContext::MapReources::GetYellowGrassGroundRightRectangle(),
            pos,
            WHITE
          );
          break;
        case 13:
          DrawTextureRec(
            AssetsContext::MapReources::mapTexture,
            AssetsContext::MapReources::GetYellowGrassGroundRectangle(),
            pos,
            WHITE
          );
          break;
        case 14:
          DrawTextureRec(
            AssetsContext::MapReources::mapTexture,
            AssetsContext::MapReources::GetYellowGrassGroundUpRectangle(),
            pos,
            WHITE
          );
          break;
        case 15:
          DrawTextureRec(
            AssetsContext::MapReources::mapTexture,
            AssetsContext::MapReources::GetYellowGrassGroundDownRectangle(),
            pos,
            WHITE
          );
          break;
      }
      if (++column == level.columns) {
        column = 0;
        row++;
      }
    }
  }

  void RenderService::DrawCamera(const Components::Controllable& player) {
    GameContext::Player::camera2d.target = { player.pos.x - (float) GetScreenWidth() / 2, player.pos.y - (float) GetScreenHeight() / 2 };
  }

  } // namespace Services

} // namespace Systems

