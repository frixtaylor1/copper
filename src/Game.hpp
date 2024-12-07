/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#ifndef GAME_HPP
#define GAME_HPP

#include "./SystemManager.hpp"
#include "./LevelManager.hpp"
#include "./Window.hpp"

#include <raylib.h>
#include <entt.hpp>

#include <terminal.hpp>

#include <assert.h>

namespace Copper {

class Game {
public:
  Game();
  ~Game();

  /**
   * No public member functions needed here. Just KISS.
   */

private:
  void run();
  void update();
  void updateTerminal();
  void updateSystems();
  void updateLevelManager();
  void initialize();
  void initializeTerminal();
  void initializeEntities(entt::registry& reg);
  void cleanUp();

private:
  Terminal*               terminal;
  bool                    open_terminal = false;
  Core::Window            window;
  Managers::SystemManager systemManager;
  Managers::LevelManager  levelManager;
};

} // namespace Copper

#endif // GAME_HPP
