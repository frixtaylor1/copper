#ifndef ASSETSCONTEXT_HPP
#define ASSETSCONTEXT_HPP

#include "raylib.h"

struct AssetsContext {
  struct MapReources {
    static inline Texture2D mapTexture;
    static inline void Load() {
      mapTexture = LoadTexture("./build/assets/mapResources.png");
    }

    static inline void Cleanup() {
      UnloadTexture(mapTexture);
    }

    static inline const Rectangle GetMountainWallRectangle() {
      return { 32.0f * 3, 32.0f * 19, 32, 32 };
    }

    static inline const Rectangle GetDoorRectangle() {
      return { 32.0f * 2, 32.0f * 10, 32, 32 };
    }

    static inline const Rectangle GetYellowGrassGroundLeftRectangle() {
      return { 32.0f * 20, 32.0f * 4, 32, 32 };
    }

    static inline const Rectangle GetYellowGrassGroundRightRectangle() {
      return { 32.0f * 22, 32.0f * 4, 32, 32 };
    }

    static inline const Rectangle GetGreenGrassGroundRectangle() {
      return { 32.0f * 21, 32.0f * 4, 32, 32 };
    }

    static inline const Rectangle GetYellowGrassGroundRectangle() {
      return { 32.0f * 21, 32.0f * 2, 32, 32 };
    }
  };
};

#endif // ASSETSCONTEXT_HPP
