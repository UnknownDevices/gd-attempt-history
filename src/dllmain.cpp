#include <core.hpp>
#include <gd_hooking/detours.hpp>
#include <gd_hooking/tramps.hpp>

DWORD WINAPI thread_func(void*) {
  using namespace gd_hooking;

  gd_att_history::init_logger();
  MH_Initialize();

  auto base = reinterpret_cast<size_t>(GetModuleHandle(0)); 
  MH_CreateHook(
    reinterpret_cast<void*>(base + 0x20CED0),
    reinterpret_cast<void*>(&PlayLayer_updateAttempts_detour),
    reinterpret_cast<void**>(&PlayLayer_updateAttempts_tramp)
  );
  MH_CreateHook(
    reinterpret_cast<void*>(base + 0x2029C0),
    reinterpret_cast<void*>(&PlayLayer_update_detour),
    reinterpret_cast<void**>(&PlayLayer_update_tramp)
  );
  MH_CreateHook(
    reinterpret_cast<void*>(base + 0x1FD3D0),
    reinterpret_cast<void*>(&PlayLayer_levelComplete_detour),
    reinterpret_cast<void**>(&PlayLayer_levelComplete_tramp)
  );
  MH_CreateHook(
    reinterpret_cast<void*>(base + 0x1FB2C0),
    reinterpret_cast<void*>(&PlayLayer_dtr_detour),
    reinterpret_cast<void**>(&PlayLayer_dtr_tramp)
  );
  MH_CreateHook(
    reinterpret_cast<void*>(base + 0x1EFAA0),
    reinterpret_cast<void*>(&PlayerObject_playerDestroyed_detour),
    reinterpret_cast<void**>(&PlayerObject_playerDestroyed_tramp)
  );
  // MH_CreateHook(
  //   reinterpret_cast<void*>(base + 0x20BF00),
  //   reinterpret_cast<void*>(&PlayLayer_resetLevel_detour),
  //   reinterpret_cast<void**>(&PlayLayer_resetLevel_tramp)
  // );
  // MH_CreateHook(
  //   reinterpret_cast<void*>(base + 0x1FB780),
  //   reinterpret_cast<void*>(&PlayLayer_init_detour),
  //   reinterpret_cast<void**>(&PlayLayer_init_tramp)
  // );
  // MH_CreateHook(
  //   reinterpret_cast<void*>(base + 0x20AF40),
  //   reinterpret_cast<void*>(&PlayLayer_updateReplay_detour),
  //   reinterpret_cast<void**>(&PlayLayer_updateReplay_tramp)
  // );
  // MH_CreateHook(
  //   reinterpret_cast<void*>(base + 0x1FB6D0),
  //   reinterpret_cast<void*>(&PlayLayer_create_detour),
  //   reinterpret_cast<void**>(&PlayLayer_create_tramp)
  // );
  // MH_CreateHook(
  //   reinterpret_cast<void*>(base + 0x1FD1C6),
  //   reinterpret_cast<void*>(&PlayLayer_init_resetLevel_detour),
  //   reinterpret_cast<void**>(&PlayLayer_init_inner_tramp)
  // );
  // MH_CreateHook(
  //   reinterpret_cast<void*>(base + 0x20A1A0),
  //   reinterpret_cast<void*>(&PlayLayer_destroyPlayer_detour),
  //   reinterpret_cast<void**>(&PlayLayer_destroyPlayer_tramp)
  // );
  // MH_CreateHook(
  //   reinterpret_cast<void*>(base + 0x1FAA90),
  //   reinterpret_cast<void*>(&PlayLayer_ctr_detour),
  //   reinterpret_cast<void**>(&PlayLayer_ctr_tramp)
  // );
  // MH_CreateHook(
  //   reinterpret_cast<void*>(base + 0x20CB60),
  //   reinterpret_cast<void*>(&PlayLayer_setupLevelStart_detour),
  //   reinterpret_cast<void**>(&PlayLayer_setupLevelStart_tramp)
  // );
  // MH_CreateHook(
  //   reinterpret_cast<void*>(base + 0x1E8200),
  //   reinterpret_cast<void*>(&PlayerObject_update_detour),
  //   reinterpret_cast<void**>(&PlayerObject_update_tramp)
  // );
  // MH_CreateHook(
  //   reinterpret_cast<void*>(base + 0x20D810),
  //   reinterpret_cast<void*>(&PlayLayer_onQuit_detour),
  //   reinterpret_cast<void**>(&PlayLayer_onQuit_tramp)
  // );
  // MH_CreateHook(
  //   reinterpret_cast<void*>(base + 0x2087D0),
  //   reinterpret_cast<void*>(&PlayLayer_timeForXPos_detour),
  //   reinterpret_cast<void**>(&PlayLayer_timeForXPos_tramp)
  // );
  // MH_CreateHook(
  //   reinterpret_cast<void*>(base + 0x20D4C0),
  //   reinterpret_cast<void*>(&PlayLayer_resumeAndRestart_detour),
  //   reinterpret_cast<void**>(&PlayLayer_resumeAndRestart_tramp)
  // );
  MH_EnableHook(MH_ALL_HOOKS);

  DWORD oldProtect;
  VirtualProtect(
    reinterpret_cast<void*>(static_cast<ptrdiff_t>(base + 0x1FD1C7)), 
    sizeof(size_t),
    PAGE_EXECUTE_READWRITE,
    &oldProtect);

  auto detour_rel_addr = static_cast<ptrdiff_t>(reinterpret_cast<size_t>(
    PlayLayer_init_resetLevel_detour) - (base + 0x1FD1C7 + sizeof(size_t)));
  memcpy(
    reinterpret_cast<void*>(static_cast<ptrdiff_t>(base + 0x1FD1C7)),
    &detour_rel_addr,
    sizeof(size_t));

  VirtualProtect(    
    reinterpret_cast<void*>(static_cast<ptrdiff_t>(base + 0x1FD1C7)), 
    sizeof(size_t), 
    oldProtect, 
    &oldProtect);

  return 0;
}

BOOL APIENTRY DllMain(HMODULE handle, DWORD reason, LPVOID reserved) {
  if (reason == DLL_PROCESS_ATTACH) {
    auto h = CreateThread(0, 0, thread_func, handle, 0, 0);
    if (h) {
      CloseHandle(h);
    }
    else {
      return FALSE;
    }
  }
  return TRUE;
}