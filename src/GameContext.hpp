/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#ifndef GAMECONTEXT_HPP
#define GAMECONTEXT_HPP

#include <entt.hpp>

struct LevelData {
  size_t rows     = 0,
         columns  = 0;
  int*   ptr      = nullptr;
};

struct GameContext {
  static inline entt::registry context;
  static inline size_t         currentLevel = 1;

  static LevelData GetLevel(int level) {
    switch (level) {
      case 1:  return { LEVEL_1_ROWS, LEVEL_1_COLUMNS, *level_1 }; break;
      case 2:  return { LEVEL_2_ROWS, LEVEL_2_COLUMNS, *level_2 }; break;
      case 3:  return { LEVEL_3_ROWS, LEVEL_3_COLUMNS, *level_3 }; break;
      case 4:  return { LEVEL_4_ROWS, LEVEL_4_COLUMNS, *level_4 }; break;
      default: return {};
    }
    return {};
  }

  static void NextLevel() {
    if (currentLevel == 4) return;
    currentLevel++;
  }

  static void PreviousLevel() {
    if (currentLevel == 1) return;
    currentLevel--;
  }

  static LevelData GetNextLevel() {
    if (currentLevel == 4) return {};
    return GetLevel(currentLevel++);
  }

  static LevelData GetPreviousLevel() {
    if (currentLevel == 1) return {};
    return GetLevel(currentLevel--);
  }

  static LevelData GetLevel() {
    return GetLevel(currentLevel);
  }

private:
  enum {
    LEVEL_1_ROWS    = 10,
    LEVEL_1_COLUMNS = 10,

    LEVEL_2_ROWS    = 10,
    LEVEL_2_COLUMNS = 10,

    LEVEL_3_ROWS    = 10,
    LEVEL_3_COLUMNS = 10,

    LEVEL_4_ROWS    = 10,
    LEVEL_4_COLUMNS = 10,
  };

  static inline int level_1[LEVEL_1_ROWS][LEVEL_1_COLUMNS] = {
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

  static inline int level_2[LEVEL_2_ROWS][LEVEL_2_COLUMNS] = {
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

  static inline int level_3[LEVEL_3_ROWS][LEVEL_3_COLUMNS] = {
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

  static inline int level_4[LEVEL_4_ROWS][LEVEL_4_COLUMNS] = {
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
};

#endif // GAMECONTEXT_HPP
