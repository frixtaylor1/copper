/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#ifndef CONTROLSYSTEM_HPP
#define CONTROLSYSTEM_HPP

#include <raylib.h>
#include <entt.hpp>

#include "ISystem.hpp"
#include "Components.hpp"
#include "GameContext.hpp"
#include "MovementCommands.hpp"

namespace Systems {

class ControlSystem : public ISystem {
public:
  void update(entt::registry& reg);

private:
  void updatePlayer(entt::registry& reg);
  static void updatePlayerPosition(Components::Controllable& movable);

  typedef bool (*ControllableCondition)(int key);
  typedef void (*ControllableAction)(Components::Controllable& movable, const Components::Speed2);

  static void playerActsByCondition(int                       key,
                                    Components::Controllable& movable,
                                    ControllableCondition     condition,
                                    Commands::ICommand&       command,
                                    Vector2                   direction);

  static inline Commands::MoveUpCommand    moveUpCommand;
  static inline Commands::MoveDownCommand  moveDownCommand;
  static inline Commands::MoveLeftCommand  moveLeftCommand;
  static inline Commands::MoveRightCommand moveRightCommand;
};

} // namespace Systems

#endif // CONTROLSYSTEM_HPP
