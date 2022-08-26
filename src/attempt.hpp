#pragma once

#include <core.hpp>

namespace gd_att_history {
  struct Attempt {
  public:
    enum class Flags : u8 {
      Normal   = 0b000000,
      Practice = 0b000010,
      StartPos = 0b000100,
      WarmUp   = 0b001000,
    };
    
    u64 start_time;
    float start_perc;
    float end_perc;
    Flags flags;

    void debug() const {
      log(std::format(
        "att. [start time [{:^7}], start perc. [{:^7.3f}], end perc. [{:^7.3f}], flags [{:^2}]]]", 
        start_time, start_perc, end_perc, static_cast<u32>(flags)));
    }
  };
}
