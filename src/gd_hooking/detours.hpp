#pragma once

#include <core.hpp>
#include <gd_hooking/tramps.hpp>
#include <level.hpp>
#include <player.hpp>

namespace gd_hooking {
  static void __fastcall PlayLayer_updateAttempts_detour(void* self, void*) {
    PlayLayer_updateAttempts_tramp(self);
    reinterpret_cast<gd_att_history::Level*>(self)->post_update_atts();
  }

  static void __fastcall PlayLayer_setupLevelStart_detour(void* self, void*, u32 var1) {
    PlayLayer_setupLevelStart_tramp(self, var1);
  }

  static DWORD* __fastcall PlayLayer_update_detour(void* self, void*, float frame_delay) {
    auto output = PlayLayer_update_tramp(self, frame_delay);
    reinterpret_cast<gd_att_history::Level*>(self)->post_update(frame_delay);
    return output;
  }

  static int __fastcall PlayLayer_updateReplay_detour(void* self, void*, float frame_delay) {
    auto output = PlayLayer_updateReplay_tramp(self, frame_delay);
    reinterpret_cast<gd_att_history::Level*>(self)->post_update_game(frame_delay);
    return output;
  }

  static void __fastcall PlayLayer_init_resetLevel_detour(void* self, void*) {
    reinterpret_cast<gd_att_history::Level*>(self)->on_first_reset_level();
    reinterpret_cast<void(__thiscall*)(void*)>(
				reinterpret_cast<size_t>(GetModuleHandle(0)) + 0x20BF00)(self);
  }

  static void* __fastcall PlayLayer_init_detour(void* self, void*, void* game_level) {
    auto output = PlayLayer_init_tramp(self, game_level);
    reinterpret_cast<gd_att_history::Level*>(self)->post_init(output, game_level);
    return output;
  }

  static void __fastcall PlayLayer_resetLevel_detour(void* self, void*) {
    PlayLayer_resetLevel_tramp(self);
  }

  static void* __fastcall PlayLayer_create_detour(void* game_level) {
    auto output = PlayLayer_create_tramp(game_level);
    gd_att_history::Level::post_create(output, game_level);
    return output;
  }

  static void* __fastcall PlayLayer_ctr_detour(void* self, void*) {
    auto output = PlayLayer_ctr_tramp(self);
    reinterpret_cast<gd_att_history::Level*>(self)->post_ctr(output);
    return output;
  }

  static void __fastcall PlayLayer_dtr_detour(void* self, void*) {
    reinterpret_cast<gd_att_history::Level*>(self)->on_dtr();
    PlayLayer_dtr_tramp(self);
  }

  static void __fastcall PlayLayer_levelComplete_detour(void* self, void*) {
    PlayLayer_levelComplete_tramp(self);
    reinterpret_cast<gd_att_history::Level*>(self)->post_level_complete();
  }

  static void __fastcall PlayLayer_resumeAndRestart_detour(void* self, void*) {
    PlayLayer_resumeAndRestart_tramp(self);
  }

  static void* __fastcall PlayLayer_onQuit_detour(void* self, void*) {
    auto output = PlayLayer_onQuit_tramp(self);
    return output;
  }

  static int __fastcall PlayLayer_destroyPlayer_detour(void* self, void*, void* player, 
    void* game_object) 
  {
    auto output = PlayLayer_destroyPlayer_tramp(self, player, game_object);
    reinterpret_cast<gd_att_history::Level*>(self)->post_destroy_player(player, game_object);
    return output;
  }

  static void __fastcall PlayerObject_playerDestroyed_detour(void* self, void*, bool is_destroyed) {
    PlayerObject_playerDestroyed_tramp(self, is_destroyed);
    reinterpret_cast<gd_att_history::Player*>(self)->post_player_destroyed(is_destroyed);
  } 
  
  static int __fastcall PlayerObject_update_detour(void* self, void*, float x) {
    auto output = PlayerObject_update_tramp(self, x);
    reinterpret_cast<gd_att_history::Player*>(self)->post_update(x);
    return output;
  } 
}