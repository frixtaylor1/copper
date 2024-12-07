/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#include "./Game.hpp"

/**
 * @formatting:
 *  - clang(kinda) formatting style
 *  - indent: 2 spaces
 *
 *  In order to understand the infrastructure of this project and the dependencies:
 *    @resouce:
 *      - https://www.umlboard.com/design-patterns/entity-component-system.html
 *
 * @dependencies: [ Entt, Raylib ]
 */

/**
 * Architecture of the system:
 *
 * The [ Game ] object encapsulates all the game logic and part of the game engine logic.
 * For example:
 *   - [ Systems ]:... Responsible for updating [ Components ].
 *   - [ Components ]: Attached to entities.
 *   - [ Entity ]:.... Simply an ID.
 *
 * The System, as a whole, has an internal module dependency:
 * the Interactive [ Terminal ] at runtime.
 *   - [ Terminal ]: Handles input (via [ Commands ] and executes [ Callbacks ])
 *       - [ Commands ]: Strings that represent actions.
 *         @TODO: Must support flags and variadic arguments.
 *       - [ Callbacks ]: Functions executed when their associated command is sent.
 */

// @TODO: the Entt dependency must be controlled.
//  - Create an EntityManager that encapsulates this dependency (entt) to improve system control.

int main(void) {
  Copper::Game game;
  return 0;
}
