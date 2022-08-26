#pragma once

#include <core.hpp>
#include <level.hpp>

namespace gd_att_history {
  class Level;

  class GameManager {
  public:
    Level& level() {
      return **reinterpret_cast<Level**>(reinterpret_cast<char*>(this) + 0x164);
    }
  };

  static GameManager& game_manager() {
    return **reinterpret_cast<GameManager**>(reinterpret_cast<uintptr_t>(
      GetModuleHandle(0)) + 0x3222D0);
  }

  static Level& level() {
    auto game_manager_addr = *reinterpret_cast<char**>(reinterpret_cast<uintptr_t>(
      GetModuleHandle(0)) + 0x3222D0);
    return **reinterpret_cast<Level**>(game_manager_addr + 0x164);
  }
}