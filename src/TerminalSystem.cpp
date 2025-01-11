/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#include "./TerminalSystem.hpp"

#include "GameContext.hpp"
#include "raylib.h"
#include "terminal.hpp"

namespace Systems {

struct TerminalContext {
  static inline Terminal* instance = nullptr;
};

TerminalSystem::TerminalSystem() {
  TerminalContext::instance = CreateTerminal();
  TerminalSetCallback(TerminalContext::instance, "nextLevel",     &GameContext::NextLevel);
  TerminalSetCallback(TerminalContext::instance, "previousLevel", &GameContext::PreviousLevel);
}

void TerminalSystem::render() {
  if (IsKeyPressed(KEY_RIGHT_CONTROL)) {
    TerminalTogle(TerminalContext::instance);
  }

  if (TerminalIsActive(TerminalContext::instance)) {
    TerminalRender(TerminalContext::instance);
    TerminalHandleInput(TerminalContext::instance);
  }
}

} // namespace Systems

