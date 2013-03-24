#include "MurmurHash3.h"

extern "C" void MurmurHash3_x86_32_test ( const void * key, int len, uint32_t seed, void * out )
{
  MurmurHash3_x86_32(key, len, seed, out);
}
