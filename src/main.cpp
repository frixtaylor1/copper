#include <raylib.h>
#include <sys/types.h>
#include <unordered_map>
#include <bitset>
#include <vector>
#include <registry.hpp>

namespace Cooper {

  /**
   * ECS Pattern...
   * @description: Begin of Entity Component Systems Pattern...
   * @resouce: https://www.umlboard.com/design-patterns/entity-component-system.html
   */
  namespace Entity {
    namespace Components {

    typedef Vector2 Speed2;
    typedef Vector3 Speed3;

    struct Player {
      Speed2    speed;
      Rectangle rectangle;
      Color     color;
    };

    }
  }

  namespace Core {

  class Window {
  public:
    Window(int width = 1024,int height = 762, const char* title = "Cooper")
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
  
  }

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

    while (window.shouldNotClose()) {

      BeginDrawing();
        /**
         * BEGIN TESTS...
         */
        auto view = reg.view<Entity::Components::Speed2, Rectangle, const Color>();
        view.each([](Entity::Components::Speed2& speed, Rectangle& rectangle, const Color color) {
          DrawRectangle(rectangle.x, rectangle.y, rectangle.width, rectangle.height, color);
          rectangle.x += speed.x;
          rectangle.y += speed.y;

          if (rectangle.y > GetScreenHeight() - rectangle.height || rectangle.y < 0) {
            speed.y *= -1;
          }

          if (rectangle.x> GetScreenWidth() - rectangle.width || rectangle.x < 0) {
            speed.x *= -1;
          }
        });
        /**
         * END TESTS...
         */
        ClearBackground(GetColor(0x181818FF));
        DrawFPS(0, 0);
      EndDrawing();
    }
  }

  void initialize() {
    SetTargetFPS(60);
  }

  void initializeEntities(entt::registry& reg) {
    for (size_t nbEntities = 0; nbEntities < 10000; nbEntities++) {
      const auto entity = reg.create();
      reg.emplace<Entity::Components::Speed2>(entity,
        (float) GetRandomValue(-3, 3),
        (float) GetRandomValue(-3, 3)
      );
      reg.emplace<Rectangle>(entity,
        (float) GetRandomValue(0, GetScreenWidth() - 50),
        (float) GetRandomValue(0, GetScreenHeight() - 50),
        50.0f, 
        50.0f 
      );
      reg.emplace<Color>(entity,
        (unsigned const char) GetRandomValue(0, 255),
        (unsigned const char) GetRandomValue(0, 255),
        (unsigned const char) GetRandomValue(0, 255),
        (unsigned const char) 255
      );
    }
  }

private:
  Core::Window window {};
};

}

int main(void) {
  Cooper::Game game;
  return 0;
}
