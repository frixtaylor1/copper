/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <raylib.h>

#include "AssetsContext.hpp"
#include "GameContext.hpp"
#include "ISystem.hpp"
#include "Components.hpp"
#include "TerminalSystem.hpp"

namespace Systems {

class RenderSystem : public ISystem {
public:
  void update(entt::registry& reg);
private:
  TerminalSystem terminalSystem;
};

  namespace Services {

  struct RenderService {
    static void DrawPlayer(const Components::Controllable& player);
    static void DrawLevel();
    static void DrawCamera(const Components::Controllable& player);
    
    struct RenderLevelCtx {
      std::map<size_t, Rectangle> ctx;
    };

    static inline std::vector<RenderLevelCtx> levelRenderCtx = {
      {
        { 
          { 1, AssetsContext::MapReources::GetMountainWallRectangle() },
          { 2, AssetsContext::MapReources::GetDoorRectangle() },
          { 10, AssetsContext::MapReources::GetGreenGrassGroundRectangle() },
          { 11, AssetsContext::MapReources::GetYellowGrassGroundLeftRectangle() },
          { 12, AssetsContext::MapReources::GetYellowGrassGroundRightRectangle() },
          { 13, AssetsContext::MapReources::GetYellowGrassGroundRectangle() },
          { 14, AssetsContext::MapReources::GetYellowGrassGroundUpRectangle() },
          { 15, AssetsContext::MapReources::GetYellowGrassGroundDownRectangle() }
        }
      },
    };
  };

  } // namespace Services

} // namespace Systems

#endif // RENDERSYSTEM_HPP
