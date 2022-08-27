#include <player.hpp>

#include <core.hpp>
#include <level.hpp>
#include <game_manager.hpp>

namespace gd_att_history {
  float Player::x() {
    return *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0x67C);
  }
  
  bool Player::is_dead() {
    return *reinterpret_cast<bool*>(reinterpret_cast<char*>(this) + 0x63F);
  }

  bool Player::has_won() {
    return *reinterpret_cast<bool*>(reinterpret_cast<char*>(this) + 0x662);
  }

  float Player::calculate_perc(float level_lenght) {
    return 100.0f * x() / level_lenght;
  }

  void Player::post_player_destroyed(bool) { // unhooked
  }

  void Player::post_update(float frame_delay) { // unhooked
  } 
}