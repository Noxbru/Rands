#include <stdio.h>
#include <stdlib.h>

typedef struct _isaac_state
{
    unsigned int wheel[256];
    unsigned int wheel2[256];
    unsigned int a, b;
    unsigned char c;

    unsigned char index;
} isaac_state;

isaac_state isaac_default_state;

isaac_state ids;

void isaac_srand(unsigned long int seed)
{
    unsigned int i;
    srand(seed);
    for(i = 0; i < 256; i++)
        ids.wheel[i]=rand();
    ids.a=0;
    ids.b=0;
    ids.c=0;
}

unsigned int isaac_rand()
{
    if(ids.index)
    {
        return ids.wheel2[ids.index++];
    }
    else
    {
        unsigned int i,x;
        unsigned int a,b;

        ids.c++;
        a=ids.a;
        b=ids.b+ids.c;
        for(i = 0; i < 256; i++)
        {
            x=ids.wheel[i];
            a= (a^(a<<13)) + ids.wheel[(i+128)%256];
            ids.wheel[i] = a+b+ids.wheel[(x>>2)%256];
            ids.wheel2[i] = x + ids.wheel[(ids.wheel[i]>>10)%256];
            b=ids.wheel2[i];
            i++;

            x=ids.wheel[i];
            a= (a^(a>>6)) + ids.wheel[(i+128)%256];
            ids.wheel[i] = a+b+ids.wheel[(x>>2)%256];
            ids.wheel2[i] = x + ids.wheel[(ids.wheel[i]>>10)%256];
            b=ids.wheel2[i];
            i++;

            x=ids.wheel[i];
            a= (a^(a<<2)) + ids.wheel[(i+128)%256];
            ids.wheel[i] = a+b+ids.wheel[(x>>2)%256];
            ids.wheel2[i] = x + ids.wheel[(ids.wheel[i]>>10)%256];
            b=ids.wheel2[i];
            i++;

            x=ids.wheel[i];
            a= (a^(a>>16)) + ids.wheel[(i+128)%256];
            ids.wheel[i] = a+b+ids.wheel[(x>>2)%256];
            ids.wheel2[i] = x + ids.wheel[(ids.wheel[i]>>10)%256];
            b=ids.wheel2[i];
        }
        ids.a=a;
        ids.b=b;
        return ids.wheel2[ids.index++];
    }
}
