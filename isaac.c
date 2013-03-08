#include <stdlib.h>
#include "rands.h"

#if ISAAC_RAND || RANDS_USE_ALL

isaac_state isaac_default_state;

void isaac_srand(unsigned long int seed)
{
    unsigned int i;
    srand(seed);
    for(i = 0; i < 256; i++)
        isaac_default_state.wheel[i]=rand();
    isaac_default_state.a=0;
    isaac_default_state.b=0;
    isaac_default_state.c=0;
    isaac_default_state.index=0;
}

void isaac_calc()
{
    unsigned int i,x,y;
    unsigned int a,b;

    isaac_default_state.c++;
    a=isaac_default_state.a;
    b=isaac_default_state.b+isaac_default_state.c;
    for(i = 0; i < 256; i++)
    {
        x = isaac_default_state.wheel[i];
        a = (a^(a<<13)) + isaac_default_state.wheel[(i+128)%256];
        isaac_default_state.wheel[i]= y = a+b+isaac_default_state.wheel[(x>>2)%256];
        isaac_default_state.wheel2[i]=b = x + isaac_default_state.wheel[(y>>10)%256];
        i++;

        x = isaac_default_state.wheel[i];
        a = (a^(a>>6)) + isaac_default_state.wheel[(i+128)%256];
        isaac_default_state.wheel[i]= y = a+b+isaac_default_state.wheel[(x>>2)%256];
        isaac_default_state.wheel2[i]=b = x + isaac_default_state.wheel[(y>>10)%256];
        i++;

        x=isaac_default_state.wheel[i];
        a= (a^(a<<2)) + isaac_default_state.wheel[(i+128)%256];
        isaac_default_state.wheel[i]= y = a+b+isaac_default_state.wheel[(x>>2)%256];
        isaac_default_state.wheel2[i]=b = x + isaac_default_state.wheel[(y>>10)%256];
        i++;

        x=isaac_default_state.wheel[i];
        a= (a^(a>>16)) + isaac_default_state.wheel[(i+128)%256];
        isaac_default_state.wheel[i]= y = a+b+isaac_default_state.wheel[(x>>2)%256];
        isaac_default_state.wheel2[i]=b = x + isaac_default_state.wheel[(y>>10)%256];
    }
    isaac_default_state.a=a;
    isaac_default_state.b=b;
}

#if RANDS_USE_STATES
inline void isaac_init_st(isaac_state **st)
{
    (*st)=malloc(sizeof(isaac_state));
}

inline void isaac_clear_st(isaac_state *st)
{
    free(st);
}

void isaac_srand_st(isaac_state *st, unsigned long int seed)
{
    unsigned int i;
    srand(seed);
    for(i = 0; i < 256; i++)
        st->wheel[i]=rand();
    st->a=0;
    st->b=0;
    st->c=0;
    st->index=0;
}

void isaac_calc_st(isaac_state *st)
{
    unsigned int i,x,y;
    unsigned int a,b;

    st->c++;
    a=st->a;
    b=st->b+st->c;
    for(i = 0; i < 256; i++)
    {
        x = st->wheel[i];
        a = (a^(a<<13)) + st->wheel[(i+128)%256];
        st->wheel[i]= y = a+b+st->wheel[(x>>2)%256];
        st->wheel2[i]=b = x + st->wheel[(y>>10)%256];
        i++;

        x = st->wheel[i];
        a = (a^(a>>6)) + st->wheel[(i+128)%256];
        st->wheel[i]= y = a+b+st->wheel[(x>>2)%256];
        st->wheel2[i]=b = x + st->wheel[(y>>10)%256];
        i++;

        x=st->wheel[i];
        a= (a^(a<<2)) + st->wheel[(i+128)%256];
        st->wheel[i]= y = a+b+st->wheel[(x>>2)%256];
        st->wheel2[i]=b = x + st->wheel[(y>>10)%256];
        i++;

        x=st->wheel[i];
        a= (a^(a>>16)) + st->wheel[(i+128)%256];
        st->wheel[i]= y = a+b+st->wheel[(x>>2)%256];
        st->wheel2[i]=b = x + st->wheel[(y>>10)%256];
    }
    st->a=a;
    st->b=b;
}
#endif

#endif
