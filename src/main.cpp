/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#include <raylib.h>
#include <entt.hpp>
#include <assert.h>
#include <terminal.hpp>

#define MUST_IMPLEMENT() assert(false && "Must Implement!")

namespace Cooper {
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
 *     - [ Commands ]: Strings that represent actions.
 *       @TODO: Must support flags and variadic arguments.
 *     - [ Callbacks ]: Functions executed when their associated command is sent.
 */


namespace Entity {
namespace Components {

typedef Vector2 Speed2;

struct Controllable {
  Vector2 pos;
  Speed2  speed;
  bool    moveEnabled = true;
};

} // namespace Components

} // namespace Entity

struct LevelData {
  size_t rows     = 0,
         columns  = 0;
  int*   ptr      = nullptr;
};

struct GameContext {
  static inline entt::registry context;
  static inline size_t         currentLevel = 1;

  static LevelData GetLevel(int level) {
    switch (level) {
      case 1:  return { LEVEL_1_ROWS, LEVEL_1_COLUMNS, *level_1 }; break;
      case 2:  return { LEVEL_2_ROWS, LEVEL_2_COLUMNS, *level_2 }; break;
      case 3:  return { LEVEL_3_ROWS, LEVEL_3_COLUMNS, *level_3 }; break;
      case 4:  return { LEVEL_4_ROWS, LEVEL_4_COLUMNS, *level_4 }; break;
      default: return {};
    }
    return {};
  }

  static void NextLevel() {
    if (currentLevel == 2) return;
    currentLevel++;
  }

  static void PreviousLevel() {
    if (currentLevel == 1) return;
    currentLevel--;
  }

  static LevelData GetNextLevel() {
    if (currentLevel == 2) return {};
    return GetLevel(currentLevel++);
  }

  static LevelData GetPreviousLevel() {
    if (currentLevel == 1) return {};
    return GetLevel(currentLevel--);
  }

  static LevelData GetLevel() {
    return GetLevel(currentLevel);
  }

private:
  enum {
    LEVEL_1_ROWS    = 10,
    LEVEL_1_COLUMNS = 10,

    LEVEL_2_ROWS    = 10,
    LEVEL_2_COLUMNS = 10,

    LEVEL_3_ROWS    = 10,
    LEVEL_3_COLUMNS = 10,

    LEVEL_4_ROWS    = 10,
    LEVEL_4_COLUMNS = 10,
  };

  static inline int level_1[LEVEL_1_ROWS][LEVEL_1_COLUMNS] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 1, 1, 1, 1, 1, 1, 0, 1 },
    { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
    { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
    { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
    { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
    { 1, 0, 1, 1, 1, 1, 1, 1, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  };

  static inline int level_2[LEVEL_2_ROWS][LEVEL_2_COLUMNS] = {
    { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 1, 1, 1, 1, 1, 0, 1 },
    { 1, 0, 1, 1, 0, 0, 0, 1, 0, 1 },
    { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
    { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
    { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
    { 1, 0, 1, 1, 1, 1, 1, 1, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  };

  static inline int level_3[LEVEL_3_ROWS][LEVEL_3_COLUMNS] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 1, 1, 1, 1, 1, 1, 0, 1 },
    { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
    { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
    { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
    { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
    { 1, 0, 1, 1, 1, 1, 1, 1, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  };

  static inline int level_4[LEVEL_4_ROWS][LEVEL_4_COLUMNS] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 1, 1, 1, 1, 1, 1, 0, 1 },
    { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
    { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
    { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
    { 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
    { 1, 0, 1, 1, 1, 1, 1, 1, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  };
};


namespace Commands {
using namespace Entity;

struct ICommand {
  virtual ~ICommand() {}
  virtual void execute(Components::Controllable& controllable) = 0;
};

struct MoveUpCommand : public ICommand {
  void execute(Components::Controllable& controllable) {
    controllable.pos.y -= controllable.speed.y;
  }
};

struct MoveDownCommand : public ICommand {
  void execute(Components::Controllable& controllable) {
    controllable.pos.y += controllable.speed.y;
  }
};

struct MoveLeftCommand : public ICommand {
  void execute(Components::Controllable& controllable) {
    controllable.pos.x -= controllable.speed.x;
  }
};

struct MoveRightCommand : public ICommand {
  void execute(Components::Controllable& controllable) {
    controllable.pos.x += controllable.speed.x;
  }
};

} // namespace Commands

namespace Systems {

struct ISystem {
  virtual ~ISystem() {}
  virtual void update(entt::registry& reg) = 0;
};

class ControlSystem : public ISystem {
public:
  void update(entt::registry& reg) {
    updatePlayer(reg);
  }

private:
  void updatePlayer(entt::registry& reg) {
    auto playerView = reg.view<Entity::Components::Controllable>();
    playerView.each(&updatePlayerPosition);
  }

  static void updatePlayerPosition(Entity::Components::Controllable& movable) {
    playerActsByCondition(KEY_W, movable, &IsKeyDown, moveUpCommand,    {0, -1});
    playerActsByCondition(KEY_S, movable, &IsKeyDown, moveDownCommand,  {0,  1});
    playerActsByCondition(KEY_A, movable, &IsKeyDown, moveLeftCommand,  {-1, 0});
    playerActsByCondition(KEY_D, movable, &IsKeyDown, moveRightCommand, {1,  0});
  }

  typedef bool (*ControllableCondition)(int key);
  typedef void (*ControllableAction)(Entity::Components::Controllable& movable, const Entity::Components::Speed2);

  static void playerActsByCondition(int                               key,
                                    Entity::Components::Controllable& movable,
                                    ControllableCondition             condition,
                                    Commands::ICommand&               command,
                                    Vector2                           direction) {
    if (!condition(key)) return;

    LevelData level = GameContext::GetLevel();
    Vector2 nextPos = movable.pos;

    // Actualiza la posición tentativa
    nextPos.y += direction.y * 15;
    nextPos.x += direction.x * 15;

    size_t cellX = (size_t) (nextPos.x + 15 ) / 30;
    size_t cellY = (size_t) (nextPos.y + 15 ) / 30;

    // Verifica límites y colisiones
    if (cellX < level.columns && cellY < level.rows) {
      size_t index =  (cellY * level.columns) + cellX;
      if (level.ptr[index] == 0) {
        command.execute(movable);
      }
    }
  }

  static inline Commands::MoveUpCommand    moveUpCommand;
  static inline Commands::MoveDownCommand  moveDownCommand;
  static inline Commands::MoveLeftCommand  moveLeftCommand;
  static inline Commands::MoveRightCommand moveRightCommand;
};

class RenderSystem : public ISystem {
public:
  void update(entt::registry& reg) {
    BeginDrawing();
      ClearBackground(GetColor(0x181818FF));

      entt::basic_view playerView = reg.view<Entity::Components::Controllable, Color>();
      playerView.each(&renderPlayer);

      DrawFPS(0, 0);
    EndDrawing();
  }

private:
  static void renderPlayer(const Entity::Components::Controllable& movable, const Color& color) {
    DrawRectangle(movable.pos.x, movable.pos.y, 30, 30, color);
  }
};

class PhysicsSystem : public ISystem {
public:
  void update(entt::registry& reg) {
    // MUST_IMPLEMENT();
  }
};

class CollisionSystem : public ISystem {
public:
  void update(entt::registry& reg) {
    // MUST_IMPLEMENT();
  }
};

class SoundSystem : public ISystem {
public:
  void update(entt::registry& reg) {
    // MUST_IMPLEMENT();
  }
};

} // namespace Systems

namespace Managers {

class SystemManager {
public:
  SystemManager() {}

  void updateSystems(entt::registry& reg) {
    for (Systems::ISystem* system : systems) {
      system->update(reg);
    }
  }

private:
  Systems::RenderSystem    renderSystem;
  Systems::PhysicsSystem   physicsSystem;
  Systems::ControlSystem   movementSystem;
  Systems::CollisionSystem collisionSystem;
  Systems::SoundSystem     soundSystem;

private:
  Systems::ISystem* systems[5] = {
    &renderSystem,
    &movementSystem,
    &physicsSystem,
    &collisionSystem,
    &soundSystem
  };
};

class LevelManager {
public:
  void update() {
    draw();
  }
  void draw() {
    LevelData level = GameContext::GetLevel();
    size_t row      = 0;
    size_t column   = 0;

    for (size_t cell = 0; cell < level.rows * level.columns; cell++) {
      if (level.ptr[cell] == 1) {
        DrawRectangle(column * 30, row * 30, 30, 30, RAYWHITE);
      }
      if (++column == level.columns) {
        column = 0;
        row++;
      }
    }
  }
};

} // namespace Managers

namespace Core {

// @TODO: the Entt dependency must be controlled.
//  - Create an EntityManager that encapsulates this dependency (entt) to improve system control.
class EntityManager {
public:
private:
};

class Window {
public:
  Window(int width = 1024, int height = 762, const char* title = "Cooper")
      : width(width), height(height), title(title) {
    initialize();
  }

  ~Window() {
    close();
  }

  static bool shouldNotClose() {
    return !WindowShouldClose();
  }

private:
  void initialize() {
    InitWindow(width, height, title);
  }

  void close() {
    CloseWindow();
  }

private:
  int         width,
              height;
  const char* title;
};

} // namespace Core

class Game {
public:
  Game() {
    initialize();
    run();
  }

  ~Game() {
    cleanUp();
  }

  /**
   * No public member functions needed here. Just Kiss.
   */

private:
  void run() {
    while (Core::Window::shouldNotClose()) {
      update();
    }
  }

  void update() {
    updateTerminal();
    updateSystems();
    updateLevelManager();
  }

  void updateTerminal() {
    if (open_terminal) {
      TerminalRender(terminal);
      TerminalHandleInput(terminal);
    }

    if (IsKeyPressed(KEY_RIGHT_CONTROL)) {
      open_terminal = !open_terminal;
    }
  }

  void updateSystems() {
    systemManager.updateSystems(GameContext::context);
  }

  void updateLevelManager() {
    levelManager.update();
  }

  void initialize() {
    SetTargetFPS(120);
    initializeEntities(GameContext::context);
    initializeTerminal();
  }

  void initializeTerminal() {
    terminal = CreateTerminal();
    TerminalSetCallback(terminal, "nextLevel",     &GameContext::NextLevel);
    TerminalSetCallback(terminal, "previousLevel", &GameContext::PreviousLevel);
  }

  void initializeEntities(entt::registry& reg) {
    entt::entity player = reg.create();
    reg.emplace<Entity::Components::Controllable>(player, Vector2 { 2.f * 15.f, 2.f * 15.f }, Entity::Components::Speed2 { 3.f, 3.f });
    reg.emplace<Color>(player, RED);
  }


  void cleanUp() {
    DestroyTerminal(terminal);
  }

private:
  Terminal*               terminal;
  bool                    open_terminal = false;
  Core::Window            window;
  Managers::SystemManager systemManager;
  Managers::LevelManager  levelManager;
};

} // namespace Cooper

int main(void) {
  Cooper::Game game;
  return 0;
}
