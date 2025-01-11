/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#include "./Window.hpp"

namespace Core {

Window::Window(int width, int height, const char* title)
    : width(width), height(height), title(title) {
  initialize();
}

Window::~Window() {
  close();
}

bool Window::ShouldNotClose() {
  return !WindowShouldClose();
}

void Window::initialize() {
  InitWindow(width, height, title);
}

void Window::close() {
  CloseWindow();
}

} // namespace Core
