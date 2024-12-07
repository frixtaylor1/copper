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

void ControlSystem::playerActsByCondition(int                               key,
                                  Components::Controllable& movable,
                                  ControllableCondition             condition,
                                  Commands::ICommand&               command,
                                  Vector2                           direction) {
  if (!condition(key)) return;

  LevelData level = GameContext::GetLevel();
  Vector2 nextPos = movable.pos;

  // Actualiza la posición tentativa
  nextPos.y += direction.y * 15;
  nextPos.x += direction.x * 15;

  size_t cellX = (size_t) (nextPos.x + 15) / 30;
  size_t cellY = (size_t) (nextPos.y + 15) / 30;

  // Verifica límites y colisiones
  if (cellX < level.columns && cellY < level.rows) {
    size_t index =  (cellY * level.columns) + cellX;
    if (level.ptr[index] == 0) {
      command.execute(movable);
    }
  }
}

}
