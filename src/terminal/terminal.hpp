/**
 * This file is part of Copper and is licensed under the GPLv3.
 * See the LICENSE file for more details.
 */
#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <string>
#include <vector>
#include <unordered_map>

class Terminal {
  typedef std::string String;

  template <typename ItemType>
  using Vector = std::vector<ItemType>;

  template <typename KeyType, typename ValueType>
  using UnorderedMap = std::unordered_map<KeyType, ValueType>;

  typedef void (*Callback)(void);

public:
  Terminal() = default;

  void handleInput();
  void render(int x, int y, int width);
  void setCallback(const String& command, Callback callback);
  void toggle();
  bool isActive();

private:
  UnorderedMap<String, Callback> callbacks;
  Vector<String>                 commandHistory;
  String                         currentInput;
  size_t                         historyLimit   = 10;
  int                            inputBoxHeight = 30;
  int                            historyHeight  = 200;
  bool                           is_active      = false;
};

extern "C" {
  Terminal* CreateTerminal();
  void      DestroyTerminal(Terminal* terminal);
  void      TerminalSetCallback(Terminal* terminal, const char* command, void (*callback)(void));
  void      TerminalHandleInput(Terminal* terminal);
  void      TerminalRender(Terminal* terminal);
  bool      TerminalIsActive(Terminal* terminal);
  void      TerminalTogle(Terminal* terminal);
}
#endif // TERMINAL_HPP
