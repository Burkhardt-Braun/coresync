#include <iostream>
#include <thread>
#include <vector>
#include <conio.h>
#include <intrin.h>

#include "synccores.h"
#define MAX_LOOPS (1000000)

#define RELEASE_ASSERT(condition) \
    do { \
        if (!(condition)) { \
            std::cerr << "Assertion failed: " << #condition << ", file " << __FILE__ << ", line " << __LINE__ << std::endl; \
            std::abort(); \
        } \
    } while (0)

/***********************************************************************/
void core(int id)
{
    for (int i = 0; i < MAX_LOOPS; ++i)
    {
        SyncCores(id);
        CoreStateType localEpoch = SyncCores_GetState(id);
        for (int j = 0; j < MAX_CORES; ++j)
        {
            CoreStateType otherEpoch = SyncCores_GetState(j);
            //the loop count MAX_LOOPS makes it necessary to check against
            // +1 , because aonther thread might have already incremented 
            // the epoch of its current state variable
            RELEASE_ASSERT(otherEpoch == localEpoch ||
                otherEpoch == localEpoch + 1);
        }
    }
}
/***********************************************************************/
int main(void)
{
    uint64_t iteration = 0;
    for (; !_kbhit();)
    {
        SyncCores_Init();
        std::vector<std::jthread> cores;
        for (auto i = 0; i < MAX_CORES; ++i)
        {
            cores.emplace_back(core, i);
        }

        ++iteration;

        if ((iteration % 10) == 0)
        {
            std::cout << iteration << "\n";
        }
    }


	return 0;
}