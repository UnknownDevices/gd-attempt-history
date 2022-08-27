#pragma once

#include <core.hpp>

namespace gd_att_history {
  class Level;

  class Player final {
  public:
    static inline float prev_x;
    float x();
    bool is_dead();
    bool has_won();
    float calculate_perc(float level_lenght);
    void post_player_destroyed(bool is_destroyed);
    void post_update(float x);
  };
}