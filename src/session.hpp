#pragma once

#include <core.hpp>
#include <attempt.hpp>

namespace gd_att_history {
  class Session final {
  public: 
    std::vector<Attempt> atts;
    bool is_an_att_ongoing;
  };
}