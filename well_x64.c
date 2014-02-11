#include "rands.h"

#if WELL_X64_RAND || RANDS_USE_ALL

well_x64_state well_x64_default_state;

void well_x64_srand(unsigned int seed)
{
    unsigned char i;
    uint64_t r;

    srand(seed);
    for(i = 0; i < 16; i++)
    {
        r=rand();
        well_x64_default_state.wheel[i]=(r<<32)+rand();
    }

    well_x64_default_state.index=0;
}

uint64_t well_x64_rand()
{
    uint64_t a,b,c,d;
    a=well_x64_default_state.wheel[well_x64_default_state.index];
    b=well_x64_default_state.wheel[(well_x64_default_state.index+13)&15];
    c=well_x64_default_state.wheel[(well_x64_default_state.index+9)&15];

    b=(a^((a<<16)&0xFFFF0000FFFF0000UL))^(b^((b<<15)&0xFFFF8000FFFF8000UL));
    c^=((c>>11)&0x001FFFFF001FFFFFUL);

    well_x64_default_state.wheel[well_x64_default_state.index]=d=b^c;
    well_x64_default_state.index=(well_x64_default_state.index+15)&15;
    a=well_x64_default_state.wheel[well_x64_default_state.index];

    d=d^(((d<<5)&0xFFFFFFE0FFFFFFE0UL)&0xDA442D24DA442D24UL);
    well_x64_default_state.wheel[well_x64_default_state.index]=a^((a<<2)&0xFFFFFFFCFFFFFFFCUL)^b^((b<<18)&0xFFFC0000FFFC0000UL)^((c<<28)&0xF0000000F0000000UL)^d;
    return well_x64_default_state.wheel[well_x64_default_state.index];
}

#if RANDS_USE_STATES
inline void well_x64_init_st(well_x64_state **st)
{
    (*st)=malloc(sizeof(well_x64_state)); 
}

inline void well_x64_clear_st(well_x64_state *st)
{
    free(st);
}

void well_x64_srand_st(well_x64_state *st, unsigned int seed)
{
    unsigned char i;
    uint64_t r;

    srand(seed);
    for(i = 0; i < 16; i++)
    {
        r=rand();
        st->wheel[i]=(r<<32)+rand();
    }

    st->index=0;
}

uint64_t well_x64_rand_st(well_x64_state *st)
{
    uint64_t a,b,c,d;
    a=st->wheel[st->index];
    b=st->wheel[(st->index+13)&15];
    c=st->wheel[(st->index+9)&15];

    b=(a^((a<<16)&0xFFFF0000FFFF0000UL))^(b^((b<<15)&0xFFFF8000FFFF8000UL));
    c^=((c>>11)&0x001FFFFF001FFFFFUL);

    st->wheel[st->index]=d=b^c;
    st->index=(st->index+15)&15;
    a=st->wheel[st->index];

    d=d^(((d<<5)&0xFFFFFFE0FFFFFFE0UL)&0xDA442D24DA442D24UL);
    st->wheel[st->index]=a^((a<<2)&0xFFFFFFFCFFFFFFFCUL)^b^((b<<18)&0xFFFC0000FFFC0000UL)^((c<<28)&0xF0000000F0000000UL)^d;
    return st->wheel[st->index];
}
#endif

#endif
