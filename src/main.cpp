#include <raylib.h>
#include <unordered_map>
#include <bitset>
#include <vector>

namespace Cooper {

  namespace Entity {
  /**
   * @description: Begin of Entity Component Systems Pattern...
   * @resouce: https://www.umlboard.com/design-patterns/entity-component-system.html
   */

  constexpr size_t MAX_COMPONENTS = 12;

  /**
   * Entity specification.
   */
  typedef uint32_t Entity;

  class ComponentManager {
    template <typename Component>
    using ComponentStorage = std::unordered_map<Entity, Component>;
  public:
    template <typename Component>
    void add(Entity entity, Component component) {
      getComponentStorage<Component>()[entity] = component;
    }

    template <typename Component>
    ComponentStorage<Component>& getComponentStorage() {
        static ComponentStorage<Component> storage;
        return storage;
    }

    template <typename Component>
    Component* get(Entity entity) {
      ComponentStorage<Component>& storage = getComponentStorage<Component>();
      return modifyComponentStorageByCondition<Component>(entity, storage, &foundComponent, &getComponent);
    }

    template <typename Component>
    void remove(Entity entity) {
      ComponentStorage<Component>& storage = getComponentStorage<Component>();
      modifyComponentStorageByCondition<Component>(entity, storage, &foundComponent, &eraseComponent);
    }

  private:
    template <typename Component>
    using FindComponentCondition = bool (*)(ComponentStorage<Component>&, Entity entity);

    template <typename Component>
    using ModifyComponentStorageCallback = Component* (*)(ComponentStorage<Component>&, Entity entity);

    template <typename Component>
    Component* modifyComponentStorageByCondition(Entity                                    entity, 
                                                 ComponentStorage<Component>&              storage, 
                                                 FindComponentCondition<Component>         condition,
                                                 ModifyComponentStorageCallback<Component> callback)
    {
      if (condition(storage, entity)) {
        return callback(storage, entity);
      }
      return nullptr;
    }

  private:
    /**
     * Begin Static callbacks...
     */
    template <typename Component>
    static bool foundComponent(ComponentStorage<Component>& componentStorage, Entity entity) {
      return (componentStorage.find(entity) != componentStorage.end());
    }

    template <typename Component>
    static Component* eraseComponent(ComponentStorage<Component>& componentStorage, Entity entity) {
      componentStorage.erase(entity);
    }

    template <typename Component>
    static Component* getComponent(ComponentStorage<Component>& componentStorage, Entity entity) {
      return &componentStorage[entity];
    }
    /**
     * End Static callbacks...
     */
  };

  class EntityManager {
  public:
    Entity create() {
      Entity entity   = nextEntity++;
      bitsets[entity] = std::bitset<MAX_COMPONENTS>();
      return entity;
    }

    template <typename Component>
    void addComponent(Entity entity) {
      bitsets[entity][getComponentTypeID<Component>()] = true;
    }

    template <typename Component>
    bool hasComponent(Entity entity) {
      return bitsets[entity][getComponentTypeID<Component>()];
    }

    const std::bitset<MAX_COMPONENTS>& getComponentMask(Entity entity) const {
      return bitsets.at(entity);
    }

  private:
    template<typename T>
    size_t getComponentTypeID() {
        static size_t typeID = nextTypeID++;
        return typeID;
    }

  private:
    static inline size_t                                    nextTypeID = 0;
    Entity                                                  nextEntity = 0;
    std::unordered_map<Entity, std::bitset<MAX_COMPONENTS>> bitsets;
  };

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
    Entity::EntityManager    entityManager;
    Entity::ComponentManager componentManager;

    for (int idx = 0; idx < 5000; idx++) {
      Entity::Entity player = entityManager.create();

      entityManager.addComponent<Rectangle>(player);
      entityManager.addComponent<Color>(player);
      entityManager.addComponent<Vector2>(player);

      componentManager.add(player, Rectangle{ (float) GetRandomValue(0, GetScreenWidth() - 50), (float) GetRandomValue(0, GetScreenHeight() - 50), 50.0f, 50.0f });
      componentManager.add(player, Color{ (unsigned const char)GetRandomValue(0, 255), (unsigned const char)GetRandomValue(0, 255), (unsigned const char)GetRandomValue(0, 255), 255 });
      componentManager.add(player, Vector2 { (float) GetRandomValue(-3, 3), (float) GetRandomValue(-3, 3)});
    }

    while (window.shouldNotClose()) {

      BeginDrawing();
        /**
         * BEGIN TESTS...
         */
        for (int idx = 0; idx < 5000; idx++) {
          Color*     color     = componentManager.get<Color>(idx);
          Vector2*   speed     = componentManager.get<Vector2>(idx); 
          Rectangle* rectangle = componentManager.get<Rectangle>(idx);

          if (rectangle && color && speed) {
            DrawRectangle(rectangle->x, rectangle->y, rectangle->width, rectangle->height, *color);

            rectangle->x += speed->x;
            rectangle->y += speed->y;

            if (rectangle->y > GetScreenHeight() - rectangle->height || rectangle->y < 0) {
              speed->y *= -1;
            }

            if (rectangle->x> GetScreenWidth() - rectangle->width || rectangle->x < 0) {
              speed->x *= -1;
            }
          }
        }
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

private:
  Core::Window window {};
};

}

int main(void) {
  Cooper::Game game;
  return 0;
}
