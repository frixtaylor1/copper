/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#include "./Game.hpp"
#include "AssetsContext.hpp"
#include "GameContext.hpp"
#include "raymath.h"

#ifndef FPS
  #define FPS 120
#endif

namespace Copper {

Game::Game() {
  initialize();
  run();
}

Game::~Game() {
  cleanUp();
}

void Game::run() {
  while (Core::Window::shouldNotClose()) update();
}

void Game::update() {
  updateSystems();
  updateLevelManager();
}

void Game::updateSystems() {
  systemManager.updateSystems(GameContext::context);
}

void Game::updateLevelManager() {
  levelManager.update();
}

void Game::initialize() {
  SetTargetFPS(FPS);
  GameContext::Load();
  initializeEntities(GameContext::context);
}

void Game::initializeEntities(entt::registry& reg) {
  entt::entity player = reg.create();
  reg.emplace<Components::Controllable>(
    player,
    Vector2Multiply(GameContext::Player::GetSize(), { 2.f, 2.f }),
    GameContext::Player::GetSpeed()
  );
  reg.emplace<Color>(player, RED);
}

void Game::cleanUp() {
  AssetsContext::MapReources::Cleanup();
}

} // namespace Copper
