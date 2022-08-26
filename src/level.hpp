#pragma once

#include <core.hpp>
#include <player.hpp>
#include <attempt.hpp>
#include <attempt_history.hpp>
#include <session.hpp>

namespace gd_att_history {
  class Player;
  class Session;
  struct AttemptHistory;
  
  class Level {
  public:
    static inline AttemptHistory att_history;
    static inline bool is_an_att_recording;
    static inline Session session;
    
    float level_lenght();
    int online_id();
    int original_id();
    Player& player_1();
    float calculate_perc(float player_x);
    static void post_create(void* self, void* game_level);
    void post_init(void* game_sound_manager, void* game_level);
    void on_first_reset_level();
    void post_ctr(void* self);
    void on_dtr();
    void post_update(float frame_delay);
    void post_update_game(float frame_delay);
    void post_update_atts();
    void post_destroy_player(void*, void*);
    void post_level_complete();
  };
}