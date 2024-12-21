/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#include "./ControlSystem.hpp"
#include "Components.hpp"
#include "CollisionSystem.hpp"

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

void ControlSystem::playerActsByCondition(int                       key,
                                          Components::Controllable& movable,
                                          ControllableCondition     condition,
                                          Commands::ICommand&       command,
                                          Vector2                   direction) {
    if (!condition(key)) return;

    if (!Services::CollisionService::PlayerCollides(movable, direction)) {
        command.execute(movable);
    }
}

}
