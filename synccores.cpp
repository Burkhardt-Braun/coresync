#include <iostream>
#include <thread>
#include <vector>
#include <conio.h>
#include <intrin.h>
#include "synccores.h"

//ensure proper cachelining in a production environment:
static std::atomic<CoreStateType> state[MAX_CORES] = { 0 };
/***********************************************************************/
CoreStateType SyncCores_GetState(uint32_t coreId)
{
    return state[coreId].load(std::memory_order_acquire);
}
/***********************************************************************/
void SyncCores(unsigned int currentCoreId)
{
    auto my_state = state[currentCoreId].fetch_add(1, std::memory_order_acq_rel) + 1;
    for (auto i = 0; i < MAX_CORES; ++i)
    {
        while (state[i].load(std::memory_order_acquire) < my_state)
        {
            /*empty*/
        }
    }
}
/***********************************************************************/
void SyncCores_Init()
{
    for (auto& s : state)
    {
        s.store(0, std::memory_order_relaxed);
    }
}