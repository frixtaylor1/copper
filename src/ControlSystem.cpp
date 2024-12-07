/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#include "./ControlSystem.hpp"

namespace Systems {

void ControlSystem::update(entt::registry& reg) {
  updatePlayer(reg);
}

void ControlSystem::updatePlayer(entt::registry& reg) {
  auto playerView = reg.view<Components::Controllable>();
  playerView.each(&updatePlayerPosition);
}

void ControlSystem::updatePlayerPosition(Components::Controllable& movable) {
  playerActsByCondition(KEY_W, movable, &IsKeyDown, moveUpCommand,    {0, -1});
  playerActsByCondition(KEY_S, movable, &IsKeyDown, moveDownCommand,  {0,  1});
  playerActsByCondition(KEY_A, movable, &IsKeyDown, moveLeftCommand,  {-1, 0});
  playerActsByCondition(KEY_D, movable, &IsKeyDown, moveRightCommand, {1,  0});
}

// @TODO: This could be in the CollisionSystem..
void ControlSystem::playerActsByCondition(int key,
                                           Components::Controllable& movable,
                                           ControllableCondition condition,
                                           Commands::ICommand& command,
                                           Vector2 direction) {
    if (!condition(key)) return;

    LevelData level = GameContext::GetLevel();
    Vector2 nextPos = movable.pos;

    nextPos.y += direction.y * 1;
    nextPos.x += direction.x * 1;

    Rectangle playerRect = { nextPos.x, nextPos.y, 30, 30 };

    bool collision = false;
    for (size_t row = 0; row < level.rows; ++row) {
        for (size_t col = 0; col < level.columns; ++col) {
            if (level.ptr[row * level.columns + col] == 1) { // If there's a wall
                Rectangle wallRect = Rectangle { (float) col * 30, (float) row * 30, 30, 30 };
                if (CheckCollisionRecs(playerRect, wallRect)) {
                    collision = true;
                    break;
                }
            }
        }
        if (collision) break;
    }

    if (!collision) {
        command.execute(movable);
    }
}

}
