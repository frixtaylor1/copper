/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#ifndef LEVELMANAGER_HPP
#define LEVELMANAGER_HPP

#include "AssetsContext.hpp"
#include "GameContext.hpp"
#include <raylib.h>

namespace Managers {

class LevelManager {
public:
  void update() {
    draw();
  }

  void draw() {
    LevelData level = GameContext::GetLevel();
    size_t row      = 0;
    size_t column   = 0;

    for (size_t cell = 0; cell < level.rows * level.columns; cell++) {
      if (level.ptr[cell] == 1) {
        DrawTextureRec(
          AssetsContext::MapReources::mapTexture,
          AssetsContext::MapReources::GetMountainWallRectangle(),
          { (float) column * 30, (float) row * 30 }, WHITE );
        // DrawRectangle(column * 30, row * 30, 30, 30, RAYWHITE);
      }
      if (++column == level.columns) {
        column = 0;
        row++;
      }
    }
  }
};

} // namespace Managers

#endif // LEVELMANAGER_HPP
