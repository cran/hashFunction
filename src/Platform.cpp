#include "Platform.h"

#include "R.h"

#include <stdio.h>

// don't need to use testRDTSC
#if 0
void testRDTSC ( void )
{
  int64_t temp = rdtsc();

  Rprintf("%d",(int)temp);
}
#endif

// no need to use SetAffinity
#if 0
#if defined(_MSC_VER)

#include <windows.h>

void SetAffinity ( int cpu )
{
  SetProcessAffinityMask(GetCurrentProcess(),cpu);
  SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
}

#else

#include <sched.h>

void SetAffinity ( int /*cpu*/ )
{
#if !defined(__CYGWIN__) && !defined(__APPLE__)
  cpu_set_t mask;
    
  CPU_ZERO(&mask);
    
  CPU_SET(2,&mask);
    
  if( sched_setaffinity(0,sizeof(mask),&mask) == -1)
  {
    Rprintf("WARNING: Could not set CPU affinity\n");
  }
#endif
}
#endif
#endif
