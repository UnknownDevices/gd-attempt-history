#pragma once

#include <core.hpp>

namespace gd_hooking {
  static void (__thiscall* PlayLayer_updateAttempts_tramp)(void* self);
  static void (__thiscall* PlayLayer_setupLevelStart_tramp)(void* self, u32 var1);
  static DWORD* (__thiscall* PlayLayer_update_tramp)(void* self, float x);
  static int (__thiscall* PlayLayer_updateReplay_tramp)(void* self, float frame_delay);
  static void* (__thiscall* PlayLayer_init_tramp)(void* self, void* game_level);
  static void (__thiscall* PlayLayer_resetLevel_tramp)(void* self);
  static void* (__fastcall* PlayLayer_create_tramp)(void* game_level);
  static void* (__thiscall* PlayLayer_ctr_tramp)(void* self);
  static void (__thiscall* PlayLayer_dtr_tramp)(void* self);
  static void (__thiscall* PlayLayer_levelComplete_tramp)(void* self);
  static void (__thiscall* PlayLayer_resumeAndRestart_tramp)(void* self);
  static void* (__thiscall* PlayLayer_onQuit_tramp)(void* self);
  static int (__fastcall* PlayLayer_destroyPlayer_tramp)(void* self, void*, void* player);
 
  static void (__thiscall* PlayerObject_playerDestroyed_tramp)(void* self, bool destroyed);
  static int (__thiscall* PlayerObject_update_tramp)(void* self, float frame_delay);
}