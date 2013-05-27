#define RANDS_USE_ALL 1

#if !RANDS_USE_ALL

#define ISAAC_RAND      1
#define ISAAC_X64_RAND  1
#define PR_RAND         1
#define WELL_RAND       1
#define WELL_X64_RAND   1
#define XOR_RAND        1

#endif

#define RANDS_USE_STATES 1

#define RANDS_PREFERRED pr_rand()
