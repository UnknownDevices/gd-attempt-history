#include <level.hpp>

#include <core.hpp>
#include <gd_hooking/tramps.hpp>
#include <game_manager.hpp>

namespace gd_att_history {
  float Level::level_lenght() {
    return *reinterpret_cast<float*>(reinterpret_cast<char*>(this) + 0x3B4);
  }

  int Level::online_id() {
    auto level_meta_addr = *reinterpret_cast<char**>(reinterpret_cast<char*>(this) + 0x488);
    return *reinterpret_cast<int*>(level_meta_addr + 0x2D4);
  }
  
  int Level::original_id() {
    auto level_meta_addr = *reinterpret_cast<char**>(reinterpret_cast<char*>(this) + 0x488);
    return *reinterpret_cast<int*>(level_meta_addr + 0xF8);
  }
  
  Player& Level::player_1() {
    return **reinterpret_cast<Player**>(reinterpret_cast<char*>(this) + 0x224);
  }

  float Level::calculate_perc(float player_x) {
    return 100.0f * player_x / level_lenght();
  }

  void Level::on_first_reset_level() { 
    is_an_att_recording = false;
    att_history.level_id = original_id();
    att_history.load();
    Player::prev_x = 0;
  } 

  void Level::on_dtr() {
    if (is_an_att_recording) {
      att_history.back().end_perc = calculate_perc(player_1().x());
      att_history.back().debug();
      is_an_att_recording = false;
    }

    att_history.save();
  }

  void Level::post_update(float frame_delay) {
    if (player_1().is_dead() & is_an_att_recording) {
      att_history.back().end_perc = calculate_perc(player_1().x());
      att_history.back().debug();
      is_an_att_recording = false;
    }

    Player::prev_x = player_1().x();
  }

  void Level::post_update_atts() {
    if (is_an_att_recording) {
      att_history.back().end_perc = calculate_perc(player_1().prev_x);
      att_history.back().debug();
      // no need to set is_an_att_recording to false as we start recording a new attempt in this same function
    }
    
    auto att = Attempt();
    att.start_time = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch()).count();
    att.start_perc = calculate_perc(player_1().x());
    // TODO: att.flags to be set
    att_history.push_back(att);

    is_an_att_recording = true;
  }
  
  void Level::post_level_complete() {
    // assumes is_an_att_recording to be true
    att_history.back().end_perc = calculate_perc(100.0f);
    att_history.back().debug();
    is_an_att_recording = false;
  }
  
  void Level::post_init(void* game_sound_manager, void* game_level) { // unhooked
  }

  void Level::post_create(void* self, void* game_level) { // unhooked
  }
  
  void Level::post_ctr(void* self) { // unhooked
  }

  void Level::post_update_game(float frame_delay) { // unhooked
  }

  void Level::post_destroy_player(void*, void*) { // unhooked
  }
  
}