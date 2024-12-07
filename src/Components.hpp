/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <raylib.h>

namespace Components {

typedef Vector2 Speed2;

struct Controllable {
  Vector2 pos;
  Speed2  speed;
  bool    moveEnabled = true;
};

} // namespace Components

#endif // COMPONENTS_HPP
