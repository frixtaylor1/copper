/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#include "./terminal.hpp"
#include "raylib.h"

void Terminal::handleInput() {
  int key = GetCharPressed();
  while (key > 0) {
    if (key >= 32 && key <= 126) {
      currentInput += static_cast<char>(key);
    }
    key = GetCharPressed();
  }

  if (IsKeyPressed(KEY_ENTER)) {
    if (!currentInput.empty()) {
      commandHistory.emplace_back(currentInput);

      if (callbacks.count(currentInput)) {
        Callback callback = callbacks.at(currentInput);
        callback();
      } else {
        commandHistory.emplace_back("Command not found!");
      }

      if (commandHistory.size() > historyLimit) {
        commandHistory.erase(commandHistory.begin());
      }
      currentInput.clear();
    }
  }

  if (IsKeyPressed(KEY_BACKSPACE) && !currentInput.empty()) {
    currentInput.pop_back();
  }
}

void Terminal::render(int x, int y, int width) {
  DrawRectangle(x, y, width, historyHeight, DARKGRAY);
  int lineY = y + 5;
  for (size_t i = 0; i <  commandHistory.size(); i++) {
    DrawText(commandHistory[i].c_str(), x + 5, lineY, 20, LIGHTGRAY);
    lineY += 25;
    if (lineY > y + historyHeight - inputBoxHeight) break;
  }

  DrawRectangle(x, y + historyHeight, width, inputBoxHeight, BLACK);
  DrawText(currentInput.c_str(), x + 5, y + historyHeight + 5, 20, RAYWHITE);
}

void Terminal::setCallback(const String& command, Callback callback) {
  callbacks[command] = callback;
}

void Terminal::toggle() {
  is_active = !is_active;
}

bool Terminal::isActive() {
  return is_active;
}

Terminal* CreateTerminal() {
  return new Terminal();
}

void DestroyTerminal(Terminal* terminal) {
  delete terminal;
}

void TerminalSetCallback(Terminal* terminal, const char* command, void (*callback)(void)) {
  terminal->setCallback(std::string{command}, callback);
}

void TerminalHandleInput(Terminal* terminal) {
  terminal->handleInput();
}

void TerminalRender(Terminal* terminal) {
  terminal->render(0, GetScreenHeight() - 240, GetScreenWidth());
}

void TerminalTogle(Terminal* terminal) {
  terminal->toggle();
}

bool TerminalIsActive(Terminal* terminal) {
  return terminal->isActive();
}
