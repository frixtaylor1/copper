/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#include "./Game.hpp"
#include "AssetsContext.hpp"
#include "GameContext.hpp"

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
  updateTerminal();
  updateSystems();
  updateLevelManager();
}

void Game::updateTerminal() {
  if (open_terminal) {
    TerminalRender(terminal);
    TerminalHandleInput(terminal);
  }

  if (IsKeyPressed(KEY_RIGHT_CONTROL)) {
    open_terminal = !open_terminal;
  }
}

void Game::updateSystems() {
  systemManager.updateSystems(GameContext::context);
}

void Game::updateLevelManager() {
  levelManager.update();
}

void Game::initialize() {
  SetTargetFPS(120);
  AssetsContext::MapReources::Load();
  initializeEntities(GameContext::context);
  initializeTerminal();
}

void Game::initializeTerminal() {
  terminal = CreateTerminal();
  TerminalSetCallback(terminal, "nextLevel",     &GameContext::NextLevel);
  TerminalSetCallback(terminal, "previousLevel", &GameContext::PreviousLevel);
}

void Game::initializeEntities(entt::registry& reg) {
  entt::entity player = reg.create();
  reg.emplace<Components::Controllable>(player, Vector2 { 2.f * 15.f, 2.f * 15.f }, Components::Speed2 { 3.f, 3.f });
  reg.emplace<Color>(player, RED);
}


void Game::cleanUp() {
  DestroyTerminal(terminal);
  AssetsContext::MapReources::Cleanup();
}

} // namespace Copper
