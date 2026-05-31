#pragma once
#include <stdint.h>
#define MAX_CORES (48)
typedef unsigned int CoreStateType;
extern void SyncCores_Init(void);
extern void SyncCores(uint32_t currentCoreId);
extern CoreStateType SyncCores_GetState(uint32_t coreId);