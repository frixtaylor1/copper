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
  };
};

#endif // ASSETSCONTEXT_HPP
