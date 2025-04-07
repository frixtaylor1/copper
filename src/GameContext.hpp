/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#ifndef GAMECONTEXT_HPP
#define GAMECONTEXT_HPP

#include "Components.hpp"
#include "raylib.h"
#include <entt.hpp>

struct LevelData {
  size_t rows     = 0,
         columns  = 0;
  int*   ptr      = nullptr;
};

struct GameContext {
public:
  struct Player {
  public:
    static Vector2            GetSize();
    static Components::Speed2 GetSpeed();
    static Camera2D&          GetCamera();
  };

public:
  static entt::registry&      GetContext();

public:
  static Color                GetBackgroundColor();
  static LevelData            GetLevel(int level);
  static size_t               GetLevelIdx();
  static void                 NextLevel();
  static void                 PreviousLevel();
  static LevelData            GetNextLevel();
  static LevelData            GetPreviousLevel();
  static LevelData            GetLevel();
  static void                 Load();

};

#endif // GAMECONTEXT_HPP
