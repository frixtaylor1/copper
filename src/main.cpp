/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */

#include <raylib.h>
#include <entt.hpp>
#include <assert.h>

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

namespace Entity {
namespace Components {

typedef Vector2 Speed2;

struct Controllable {
  Vector2 pos;
  Speed2  speed;
};

}

namespace Commands {

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

class MovementSystem : public ISystem {
public:
  void update(entt::registry& reg) {
    updatePlayer(reg);
  }

private:
  void updatePlayer(entt::registry& reg) {
    auto playerView = reg.view<Entity::Components::Controllable>();
    playerView.each(&updatePlayerPosition);
  }

private:
  static void updatePlayerPosition(Entity::Components::Controllable& movable) {
    playerActsByCondition(KEY_W, movable, &IsKeyDown, moveUpCommand);
    playerActsByCondition(KEY_S, movable, &IsKeyDown, moveDownCommand);
    playerActsByCondition(KEY_A, movable, &IsKeyDown, moveLeftCommand);
    playerActsByCondition(KEY_D, movable, &IsKeyDown, moveRightCommand);
  }

  typedef bool (*ControllableCondition)(int key);
  typedef void (*ControllableAction)(Entity::Components::Controllable& movable, const Entity::Components::Speed2);
  static void playerActsByCondition(int                               key,
                                    Entity::Components::Controllable& movable,
                                    ControllableCondition             condition,
                                    Commands::ICommand&               command) {
    if (condition(key)) command.execute(movable);
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
    DrawRectangle(movable.pos.x, movable.pos.y, 50, 50, color);
  }
};

class PhysicsSystem : public ISystem {
public:
  void update(entt::registry& reg) {
    MUST_IMPLEMENT();
  }
};

class CollisionSystem : public ISystem {
  void update(entt::registry& reg) {
    MUST_IMPLEMENT();
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
  Systems::MovementSystem  movementSystem;
  Systems::CollisionSystem collisionSystem;

private:
  Systems::ISystem* systems[4] = {
    &renderSystem,
    &movementSystem,
    &physicsSystem,
    &collisionSystem
  };
};

} // namespace Managers

} // namespace Entity

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

struct LevelData {
  size_t rows     = 0,
         columns  = 0;
  int*   ptr      = nullptr;
};

struct GameContext {
  static inline entt::registry context;
  static inline int            currentLevel = 1;

  static LevelData getLevel(int level) {
    switch (level) {
      case 1:  return { LEVEL_1_ROWS, LEVEL_1_COLUMNS, *level_1 }; break;
      case 2:  return { LEVEL_2_ROWS, LEVEL_2_COLUMNS, *level_2 }; break;
      case 3:  return { LEVEL_3_ROWS, LEVEL_3_COLUMNS, *level_3 }; break;
      case 4:  return { LEVEL_4_ROWS, LEVEL_4_COLUMNS, *level_4 }; break;
      default: return {};
    }
    return {};
  }

  static LevelData getNextLevel() {
    if (currentLevel == 2) { return {}; }
    return getLevel(currentLevel++);
  }

  static LevelData getPreviousLevel() {
    if (currentLevel == 1) { return {}; }
    return getLevel(currentLevel--);
  }

  static LevelData getLevel() {
    return getLevel(currentLevel);
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
    LEVEL_4_COLUMNS = 10
  };

  static inline int level_1[LEVEL_1_ROWS][LEVEL_1_COLUMNS] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  };

  static inline int level_2[LEVEL_2_ROWS][LEVEL_2_COLUMNS] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  };

  static inline int level_3[LEVEL_3_ROWS][LEVEL_3_COLUMNS] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  };

  static inline int level_4[LEVEL_4_ROWS][LEVEL_4_COLUMNS] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  };
};


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
      systemManager.updateSystems(GameContext::context);
    }
  }

  void initialize() {
    SetTargetFPS(120);
    initializeEntities(GameContext::context);
  }

  void initializeEntities(entt::registry& reg) {
    entt::entity player = reg.create();
    reg.emplace<Entity::Components::Controllable>(player, Vector2 { 10.f, 10.f }, Entity::Components::Speed2 { 3.f, 3.f });
    reg.emplace<Color>(player, RED);
  }

  void cleanUp() {
    /** Future shader cleanup and stuff or some context shit cleanup */
  }

private:
  Core::Window                    window;
  Entity::Managers::SystemManager systemManager;
};

} // namespace Cooper

int main(void) {
  Cooper::Game game;
  return 0;
}
