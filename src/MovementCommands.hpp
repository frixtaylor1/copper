/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#ifndef MOVEMENTCOMMANDS_HPP
#define MOVEMENTCOMMANDS_HPP

#include "./Components.hpp"

namespace Commands {

struct ICommand {
  virtual ~ICommand() {}
  virtual void execute(Components::Controllable& controllable) = 0;
};

struct MoveUpCommand : public ICommand {
  void execute(Components::Controllable& controllable) {
    controllable.pos.y -= controllable.speed.y;
  }
};

struct MoveDownCommand : public ICommand {
  void execute(Components::Controllable& controllable) {
    controllable.pos.y += controllable.speed.y;
  }
};

struct MoveLeftCommand : public ICommand {
  void execute(Components::Controllable& controllable) {
    controllable.pos.x -= controllable.speed.x;
  }
};

struct MoveRightCommand : public ICommand {
  void execute(Components::Controllable& controllable) {
    controllable.pos.x += controllable.speed.x;
  }
};

} // namespace Commands

#endif // MOVEMENTCOMMANDS_HPP
