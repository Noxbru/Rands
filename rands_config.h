#define RANDS_USE_ALL 1

#if !RANDS_USE_ALL

#define ISAAC_RAND      1
#define ISAAC_X64_RAND  1
#define PR_RAND         1
#define PR_SSE_RAND     1 // Needs sse2 at least
#define MT_RAND         1
#define WELL_RAND       1
#define WELL_X64_RAND   1
#define XOR_RAND        1

#endif

#define STDLIB_RAND_TEST 1

#define RANDS_USE_STATES 1

#define RANDS_PREFERRED() pr_rand()
