typedef struct _mt_state 
{
    unsigned int wheel[624];
    unsigned int wheel2[624];
    unsigned int index;
} mt_state;

mt_state mt_default_state;

void mt_srand(unsigned long int seed)
{
    unsigned int i;
    srand(seed);
    for(i = 0; i < 624; i++)
        mt_default_state.wheel[i]=rand();
    mt_default_state.index=0;
}

void mt_calc()
{
    unsigned int i,y;
    static unsigned int mt_magic[2] = {0,0x9908b0df};

    for(i = 0; i < 624; i++)
    {
        y = (mt_default_state.wheel[i] & 0x80000000) | \
            (mt_default_state.wheel[(i+1)%624] & 0x7fffffff);
        mt_default_state.wheel[i] = mt_default_state.wheel[(i+397)%624] ^ (y>>1) ^ mt_magic[y&1];

        y = mt_default_state.wheel[i];
        y^= (y>>11);
        y^= ((y<<7)&0x9d2c5680);
        y^= ((y<<15)&0xefc60000);
        y^= (y>>18);
        mt_default_state.wheel2[i] = y;
    }
    mt_default_state.index = 0;
}

unsigned int mt_rand()
{
    unsigned int r;
    if(!mt_default_state.index)
        mt_calc();
    r = mt_default_state.wheel2[mt_default_state.index];
    mt_default_state.index = (mt_default_state.index + 1)%624;
    return r;
}
