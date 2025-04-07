/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#include "./GameContext.hpp"
#include "AssetsContext.hpp"
#include "raylib.h"


struct PlayerContext {
  static inline Camera2D camera2d = {
   Vector2 {
     (float) GetScreenWidth() / 2,
     (float) GetScreenHeight() / 2
   },
   Vector2 {
     0.0f, 0.0f
   },
   0.0f,
   1.0f,
  };
};

struct LevelContext {
  enum {
    LEVEL_1_ROWS    = 32,
    LEVEL_1_COLUMNS = 32,

    LEVEL_2_ROWS    = 10,
    LEVEL_2_COLUMNS = 10,

    LEVEL_3_ROWS    = 10,
    LEVEL_3_COLUMNS = 10,

    LEVEL_4_ROWS    = 10,
    LEVEL_4_COLUMNS = 10,
  };

  static inline size_t  currentLevel = 1;

  static int level_1[LEVEL_1_ROWS][LEVEL_1_COLUMNS];
  static int level_2[LEVEL_2_ROWS][LEVEL_2_COLUMNS];
  static int level_3[LEVEL_3_ROWS][LEVEL_3_COLUMNS];
  static int level_4[LEVEL_4_ROWS][LEVEL_4_COLUMNS];
};

struct Context {
  static inline entt::registry context;
};

entt::registry& GameContext::GetContext() {
  return Context::context;
}

Camera2D& GameContext::Player::GetCamera() {
  return PlayerContext::camera2d;
}

Color GameContext::GetBackgroundColor() {
  return GetColor(0x161616FF);
}

Vector2 GameContext::Player::GetSize() {
  return { 15.f, 15.f };
}

Components::Speed2 GameContext::Player::GetSpeed() {
  return { 1.0f,1.0f };
}

void GameContext::NextLevel() {
  if (LevelContext::currentLevel == 4) return;
  LevelContext::currentLevel++;
}

void GameContext::PreviousLevel() {
  if (LevelContext::currentLevel == 1) return;
  LevelContext::currentLevel--;
}

LevelData GameContext::GetLevel(int level) {
  switch (level) {
    case 1:  return { LevelContext::LEVEL_1_ROWS, LevelContext::LEVEL_1_COLUMNS, *LevelContext::level_1 }; break;
    case 2:  return { LevelContext::LEVEL_2_ROWS, LevelContext::LEVEL_2_COLUMNS, *LevelContext::level_2 }; break;
    case 3:  return { LevelContext::LEVEL_3_ROWS, LevelContext::LEVEL_3_COLUMNS, *LevelContext::level_3 }; break;
    case 4:  return { LevelContext::LEVEL_4_ROWS, LevelContext::LEVEL_4_COLUMNS, *LevelContext::level_4 }; break;
    default: return {};
  }
  return {};
}

size_t GameContext::GetLevelIdx() {
  return LevelContext::currentLevel - 1;
}

LevelData GameContext::GetNextLevel() {
  if (LevelContext::currentLevel == 4) return {};
  return GetLevel(LevelContext::currentLevel++);
}

LevelData GameContext::GetPreviousLevel() {
  if (LevelContext::currentLevel == 1) return {};
  return GetLevel(LevelContext::currentLevel--);
}

LevelData GameContext::GetLevel() {
  return GetLevel(LevelContext::currentLevel);
}

void GameContext::Load() {
  AssetsContext::MapReources::Load();
}

int LevelContext::level_1[LevelContext::LEVEL_1_ROWS][LevelContext::LEVEL_1_COLUMNS] = {
  { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 1 },
  { 1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13,  1,  1,  1,  1,  1,  1, 13, 13, 13,  1,  1,  1,  1,  1,  1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13,  1, 13, 13, 13, 13, 13, 10, 10, 10, 13, 13, 13, 13, 13,  1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13,  1, 13, 13, 13, 13,  1, 11, 10, 12,  1, 13, 13, 13, 13,  1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13,  1, 13, 13, 13, 13,  1, 11, 10, 12,  1, 13, 13, 13, 13,  1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13,  1, 13, 13, 13, 13,  1, 11, 10, 12,  1, 13, 13, 13, 13,  1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13,  1,  1,  1,  1,  1,  1, 11, 10, 12,  1,  1,  1,  1,  1,  1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13, 13, 13, 13, 13, 13, 13, 11, 10, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13, 13, 13, 13, 13, 13, 13, 11, 10, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13, 13, 13, 13, 13, 13, 13, 11, 10, 12, 14, 14, 14, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13, 13, 13, 13, 13, 13, 13, 11, 10, 10, 10, 10, 10, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13, 13, 13, 13, 13, 13, 13, 11, 10, 12, 15, 15, 15, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13, 13, 13, 13, 13, 13, 13, 11, 10, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 1 },
  { 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 1 },
};

int LevelContext::level_2[LevelContext::LEVEL_2_ROWS][LevelContext::LEVEL_2_COLUMNS] = {
  { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 1, 1, 1, 1, 1, 0, 1 },
  { 1, 0, 1, 1, 0, 0, 0, 1, 0, 1 },
  { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
  { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
  { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
  { 1, 0, 1, 1, 1, 1, 1, 1, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};

int LevelContext::level_3[LevelContext::LEVEL_3_ROWS][LevelContext::LEVEL_3_COLUMNS] = {
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 1, 1, 1, 1, 1, 1, 0, 1 },
  { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
  { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
  { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
  { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
  { 1, 0, 1, 1, 1, 1, 1, 1, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};

int LevelContext::level_4[LevelContext::LEVEL_4_ROWS][LevelContext::LEVEL_4_COLUMNS] = {
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 1, 1, 0, 1, 1, 1, 0, 1 },
  { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
  { 1, 0, 1, 1, 0, 0, 0, 1, 0, 1 },
  { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
  { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
  { 1, 0, 1, 1, 1, 1, 0, 1, 0, 1 },
  { 1, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
 };
