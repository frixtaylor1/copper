/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#ifndef WINDOW_HPP 
#define WINDOW_HPP 

#include <raylib.h>

namespace Core {

class Window {
public:
  Window(int width = 1024, int height = 762, const char* title = "Cooper");
  ~Window();

  static bool shouldNotClose();

private:
  void initialize();
  void close();

private:
  int         width,
              height;
  const char* title;
};

} // namespace Core

#endif // WINDOW_HPP
