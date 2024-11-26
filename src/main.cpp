#include <raylib.h>
#include <entt.hpp>

namespace Cooper {

/**
 * @formatting: clang formatting style
 * @resouce: https://www.umlboard.com/design-patterns/entity-component-system.html
 * @dependency: Entt
 */
namespace Entity {
namespace Components {

typedef Vector2 Speed2;

struct Movable {
  Vector2 pos;
};

}

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
  typedef bool (*MovableCondition)(int key);
  typedef void (*MovableAction)(Entity::Components::Movable& movable, const Entity::Components::Speed2);
  static void playerActsByCondition(int                       key,
                             Entity::Components::Movable&     movable,
                             const Entity::Components::Speed2 speed,
                             MovableCondition                 condition,
                             MovableAction                    callback) {
    if (condition(key)) callback(movable, speed);
  }

  void updatePlayer(entt::registry& reg) {
    auto playerView = reg.view<Entity::Components::Speed2, Entity::Components::Movable>();
    playerView.each(&updatePlayerPosition);
  }

  static void updatePlayerPosition(const Entity::Components::Speed2& speed, Entity::Components::Movable& movable) {
    playerActsByCondition(KEY_W, movable, speed, &IsKeyDown, &movePlayerUp);
    playerActsByCondition(KEY_S, movable, speed, &IsKeyDown, &movePlayerDown);
    playerActsByCondition(KEY_A, movable, speed, &IsKeyDown, &movePlayerLeft);
    playerActsByCondition(KEY_D, movable, speed, &IsKeyDown, &movePlayerRight);
  }

  static void movePlayerUp(Entity::Components::Movable& movable, const Entity::Components::Speed2 speed) {
    movable.pos.y -= speed.y;
  }

  static void movePlayerDown(Entity::Components::Movable& movable, const Entity::Components::Speed2 speed) {
    movable.pos.y += speed.y;
  }

  static void movePlayerLeft(Entity::Components::Movable& movable, const Entity::Components::Speed2 speed) {
    movable.pos.x -= speed.x;
  }

  static void movePlayerRight(Entity::Components::Movable& movable, const Entity::Components::Speed2 speed) {
    movable.pos.x += speed.x;
  }
};

class RenderSystem : public ISystem {
public:
  void update(entt::registry& reg) {
    BeginDrawing();
      ClearBackground(GetColor(0x181818FF));

      auto playerView = reg.view<Entity::Components::Movable, Color>();
      playerView.each(&renderPlayer);

      DrawFPS(0, 0);
    EndDrawing();
  }

private:
  static void renderPlayer(const Entity::Components::Movable& movable, const Color& color) {
    DrawRectangle(movable.pos.x, movable.pos.y, 50, 50, color);
  }
};

class PhysicsSystem : public ISystem {
public:
  void update(entt::registry& reg) {
  }
};

} // namespace Systems

} // namespace Entity

namespace Core {

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

private:
  void run() {
    entt::registry reg;
    initializeEntities(reg);

    Entity::Systems::MovementSystem movementSystem;
    Entity::Systems::RenderSystem   renderSystem;
    Entity::Systems::PhysicsSystem  physicsSystem;

    Entity::Systems::ISystem* systems[] = {
      &movementSystem,
      &renderSystem,
      &physicsSystem
    };

    while (Core::Window::shouldNotClose()) {
      for (Entity::Systems::ISystem* system : systems) {
        system->update(reg);
      }
    }
  }

  void initialize() { SetTargetFPS(60); }

  void initializeEntities(entt::registry& reg) {
    entt::entity player = reg.create();
    reg.emplace<Entity::Components::Speed2>(player, 6.0f, 6.0f);
    reg.emplace<Entity::Components::Movable>(player, Vector2 { 10.f, 10.f });
    reg.emplace<Color>(player, RED);
  }

private:
  Core::Window window{};
};

} // namespace Cooper

int main(void) {
  Cooper::Game game;
  return 0;
}
