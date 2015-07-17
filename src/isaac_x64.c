#include "rands.h"

#if ISAAC_X64_RAND || RANDS_USE_ALL

isaac_x64_state isaac_x64_default_state;

void isaac_x64_srand(unsigned int seed)
{
    unsigned int i;
    uint64_t r;
    srand(seed);
    for(i = 0; i < 256; i++)
    {
        r=rand();
        isaac_x64_default_state.wheel[i]=(r<<32)+rand();
    }
    isaac_x64_default_state.a=0;
    isaac_x64_default_state.b=0;
    isaac_x64_default_state.c=0;
    isaac_x64_default_state.index=0;
}

void isaac_x64_calc()
{
    unsigned int i;
    uint64_t x,y;
    uint64_t a,b;

    isaac_x64_default_state.c++;
    a=isaac_x64_default_state.a;
    b=isaac_x64_default_state.b+isaac_x64_default_state.c;
    for(i = 0; i < 256; i++)
    {
        x = isaac_x64_default_state.wheel[i];
        a =~(a^(a<<21)) + isaac_x64_default_state.wheel[(i+128)%256];
        isaac_x64_default_state.wheel[i]= y = a+b+isaac_x64_default_state.wheel[(x>>3)%256];
        isaac_x64_default_state.wheel2[i]=b = x + isaac_x64_default_state.wheel[(y>>11)%256];
        i++;

        x = isaac_x64_default_state.wheel[i];
        a = (a^(a>>5)) + isaac_x64_default_state.wheel[(i+128)%256];
        isaac_x64_default_state.wheel[i]= y = a+b+isaac_x64_default_state.wheel[(x>>3)%256];
        isaac_x64_default_state.wheel2[i]=b = x + isaac_x64_default_state.wheel[(y>>11)%256];
        i++;

        x=isaac_x64_default_state.wheel[i];
        a= (a^(a<<12)) + isaac_x64_default_state.wheel[(i+128)%256];
        isaac_x64_default_state.wheel[i]= y = a+b+isaac_x64_default_state.wheel[(x>>3)%256];
        isaac_x64_default_state.wheel2[i]=b = x + isaac_x64_default_state.wheel[(y>>11)%256];
        i++;

        x=isaac_x64_default_state.wheel[i];
        a= (a^(a>>33)) + isaac_x64_default_state.wheel[(i+128)%256];
        isaac_x64_default_state.wheel[i]= y = a+b+isaac_x64_default_state.wheel[(x>>3)%256];
        isaac_x64_default_state.wheel2[i]=b = x + isaac_x64_default_state.wheel[(y>>11)%256];
    }
    isaac_x64_default_state.a=a;
    isaac_x64_default_state.b=b;
}

#if RANDS_USE_STATES
inline void isaac_x64_init_st(isaac_x64_state **st)
{
    (*st)=malloc(sizeof(isaac_x64_state));
}

inline void isaac_x64_clear_st(isaac_x64_state *st)
{
    free(st);
}

void isaac_x64_srand_st(isaac_x64_state *st, unsigned int seed)
{
    unsigned int i;
    uint64_t r;
    srand(seed);
    for(i = 0; i < 256; i++)
    {
        r=rand();
        st->wheel[i]=(r<<32)+rand();
    }
    st->a=0;
    st->b=0;
    st->c=0;
    st->index=0;
}

void isaac_x64_calc_st(isaac_x64_state *st)
{
    unsigned int i;
    uint64_t x,y;
    uint64_t a,b;

    st->c++;
    a=st->a;
    b=st->b+st->c;
    for(i = 0; i < 256; i++)
    {
        x = st->wheel[i];
        a = ~(a^(a<<21)) + st->wheel[(i+128)%256];
        st->wheel[i]= y = a+b+st->wheel[(x>>3)%256];
        st->wheel2[i]=b = x + st->wheel[(y>>11)%256];
        i++;

        x = st->wheel[i];
        a = (a^(a>>5)) + st->wheel[(i+128)%256];
        st->wheel[i]= y = a+b+st->wheel[(x>>3)%256];
        st->wheel2[i]=b = x + st->wheel[(y>>11)%256];
        i++;

        x=st->wheel[i];
        a= (a^(a<<12)) + st->wheel[(i+128)%256];
        st->wheel[i]= y = a+b+st->wheel[(x>>3)%256];
        st->wheel2[i]=b = x + st->wheel[(y>>11)%256];
        i++;

        x=st->wheel[i];
        a= (a^(a>>33)) + st->wheel[(i+128)%256];
        st->wheel[i]= y = a+b+st->wheel[(x>>3)%256];
        st->wheel2[i]=b = x + st->wheel[(y>>11)%256];
    }
    st->a=a;
    st->b=b;
}
#endif

#endif
