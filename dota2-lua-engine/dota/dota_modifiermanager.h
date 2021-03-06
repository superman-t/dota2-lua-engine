// Copyright 2013 Karl Skomski - GPL v3
#pragma once

#include "utils/global_address_retriever.h"

namespace dota {

class DotaBuff {
 public:
  const char* GetName() {
    return *(const char**)(this + 0xC);
  }
  int GetStackCount() {
    typedef int ( __thiscall* OriginalFn )(void* thisptr);
    return utils::GetVtableFunction<OriginalFn>(this, 17)(this);
  }
  float GetDieTime() {
    typedef float ( __thiscall* OriginalFn )(void* thisptr);
    return utils::GetVtableFunction<OriginalFn>(this, 20)(this);
  }
  float GetDuration() {
    typedef float ( __thiscall* OriginalFn )(void* thisptr);
    return utils::GetVtableFunction<OriginalFn>(this, 21)(this);
  }
  const char* GetTexture() {
    typedef const char* ( __thiscall* OriginalFn )(void* thisptr);
    return utils::GetVtableFunction<OriginalFn>(this, 22)(this);
  }
  float GetRemainingTime() {
    typedef float ( __thiscall* OriginalFn )(void* thisptr);
    return utils::GetVtableFunction<OriginalFn>(this, 23)(this);
  }
  float GetElapsedTime() {
    typedef float ( __thiscall* OriginalFn )(void* thisptr);
    return utils::GetVtableFunction<OriginalFn>(this, 24)(this);
  }
};

class ModifierManager {
 public:
  int GetModifierDefaultParams() {
    return GlobalAddressRetriever::GetInstance()
      .GetDynamicAddress("ModifierDefaultParams");
  }
  float GetModifier_Constant_Additive_Internal(int modifier_index) {
    uint32_t address = GlobalAddressRetriever::GetInstance()
      .GetStaticAddress(
        "ModifierManager::GetModifier_Constant_Additive_Internal");

    float constant = 0;
    int default_params_address = GetModifierDefaultParams();

    __asm {
      push default_params_address
      mov eax, modifier_index
      mov edx, this
      call address
      movss [constant], xmm0
    }

    return constant;
  }

  int GetCurrentBuffCount() {
    return *(int*)(this + 0x14);
  }

  DotaBuff* GetBuffByIndex(int index) {
   int max_buff_index = GetCurrentBuffCount();
   uint32_t buff_array = *(uint32_t*)(this + 0x8);

    if (max_buff_index > index) {
      DotaBuff* buff = *(DotaBuff**)(buff_array + 0x4 * index);
      if (buff != nullptr && !(*(char*)(buff + 0x10) & 1)) {
        return buff;
      }
    }
    return nullptr;
  }
};

}  // namespace dota
