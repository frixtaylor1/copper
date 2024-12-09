/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#include "./CollisionSystem.hpp"
#include "GameContext.hpp"

namespace Systems {

  void CollisionSystem::update(entt::registry& reg) {
  }

  namespace Services {

  bool CollisionService::PlayerCollides(const Components::Controllable& player, const Vector2& direction) {
      LevelData level = GameContext::GetLevel();
      Vector2 nextPos = player.pos;

      nextPos.y += direction.y;
      nextPos.x += direction.x;

      Rectangle playerRect = { nextPos.x, nextPos.y,
          GameContext::Player::GetSize().x,
          GameContext::Player::GetSize().y
      };

      bool collision = false;
      for (size_t row = 0; row < level.rows; ++row) {
          for (size_t col = 0; col < level.columns; ++col) {
              if (level.ptr[row * level.columns + col] == 1) {
                  Rectangle wallRect = Rectangle { (float) col * 30, (float) row * 30, 30, 30 };
                  if (CheckCollisionRecs(playerRect, wallRect)) {
                      collision = true;
                      break;
                  }
              }
          }
          if (collision) break;
      }

      return collision;
  }

  }
}
