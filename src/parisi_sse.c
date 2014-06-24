#include "rands.h"

#if __SSE2__
#if PR_SSE_RAND || RANDS_USE_ALL

pr_sse_state pr_sse_default_state;

void pr_sse_srand(unsigned int seed)
{
    srand(seed);
    unsigned char i;
    pr_sse_default_state.index=0;
    for(i = 0; i != 255; i++)
        pr_sse_default_state.wheel[i]=rand();
    pr_sse_default_state.wheel[255]=rand();
}

void pr_sse_calc()
{
    unsigned int i;
    __m128i a,b,c,d;

    for(i = 0; i < 24; i+=4)
    {
        a = _mm_loadu_si128((__m128i *)&pr_sse_default_state.wheel[(i-24)&0xff]);
        b = _mm_loadu_si128((__m128i *)&pr_sse_default_state.wheel[(i-55)&0xff]);
        c = _mm_loadu_si128((__m128i *)&pr_sse_default_state.wheel[(i-61)&0xff]);
        d = _mm_add_epi32(a,b);
        _mm_storeu_si128((__m128i *)&pr_sse_default_state.wheel[i], d);
        _mm_storeu_si128((__m128i *)&pr_sse_default_state.wheel2[i], _mm_xor_si128(c,d));
    }

    for(; i < 52; i+=4)
    {
        a = _mm_loadu_si128((__m128i *)&pr_sse_default_state.wheel[i-24]);
        b = _mm_loadu_si128((__m128i *)&pr_sse_default_state.wheel[(i-55)&0xff]);
        c = _mm_loadu_si128((__m128i *)&pr_sse_default_state.wheel[(i-61)&0xff]);
        d = _mm_add_epi32(a,b);
        _mm_storeu_si128((__m128i *)&pr_sse_default_state.wheel[i], d);
        _mm_storeu_si128((__m128i *)&pr_sse_default_state.wheel2[i], _mm_xor_si128(c,d));
    }

    for(; i < 64; i++)
    {
        pr_sse_default_state.wheel[i] = pr_sse_default_state.wheel[(i-24)] + \
                                        pr_sse_default_state.wheel[(i-55)&0xff];
        pr_sse_default_state.wheel2[i]= pr_sse_default_state.wheel[i] ^      \
                                        pr_sse_default_state.wheel[(i-61)&0xff];
    }

    for(; i < 256; i+=4)
    {
        a = _mm_loadu_si128((__m128i *)&pr_sse_default_state.wheel[(i-24)]);
        b = _mm_loadu_si128((__m128i *)&pr_sse_default_state.wheel[(i-55)]);
        c = _mm_loadu_si128((__m128i *)&pr_sse_default_state.wheel[(i-61)]);
        d = _mm_add_epi32(a,b);
        _mm_storeu_si128((__m128i *)&pr_sse_default_state.wheel[i], d);
        _mm_storeu_si128((__m128i *)&pr_sse_default_state.wheel2[i], _mm_xor_si128(c,d));
    }

    /* Code, supposing there would be no problems
     * at the limits of the wheels
     *
     * for(i = 0; i < 256; i+=4)
     * {
     *     a = _mm_loadu_si128((__m128i *)&pr_sse_default_state.wheel[(i-24)&0xff]);
     *     b = _mm_loadu_si128((__m128i *)&pr_sse_default_state.wheel[(i-55)&0xff]);
     *     c = _mm_loadu_si128((__m128i *)&pr_sse_default_state.wheel[(i-61)&0xff]);
     *     d = _mm_add_epi32(a,b);
     *     *(__m128i *)&pr_sse_default_state.wheel[i] = d;
     *     *(__m128i *)&pr_sse_default_state.wheel2[i] = _mm_xor_si128(c,d);
     * }
     */
    pr_sse_default_state.index=0;
}

#if RANDS_USE_STATES
inline void pr_sse_init_st(pr_sse_state **st)
{
    (*st)=malloc(sizeof(pr_sse_state)); 
}

inline void pr_sse_clear_st(pr_sse_state *st)
{
    free(st);
}

void pr_sse_srand_st(pr_sse_state *st, unsigned int seed)
{
    srand(seed);
    unsigned char i;
    st->index=0;
    for(i = 0; i != 255; i++)
        st->wheel[i]=rand();
    st->wheel[255]=rand();
}

void pr_sse_calc_st(pr_sse_state *st)
{
    unsigned int i;
    __m128i a,b,c,d;

    for(i = 0; i < 24; i+=4)
    {
        a = _mm_loadu_si128((__m128i *)&st->wheel[(i-24)&0xff]);
        b = _mm_loadu_si128((__m128i *)&st->wheel[(i-55)&0xff]);
        c = _mm_loadu_si128((__m128i *)&st->wheel[(i-61)&0xff]);
        d = _mm_add_epi32(a,b);
        _mm_storeu_si128((__m128i *)&st->wheel[i], d);
        _mm_storeu_si128((__m128i *)&st->wheel2[i], _mm_xor_si128(c,d));
    }

    for(; i < 52; i+=4)
    {
        a = _mm_loadu_si128((__m128i *)&st->wheel[i-24]);
        b = _mm_loadu_si128((__m128i *)&st->wheel[(i-55)&0xff]);
        c = _mm_loadu_si128((__m128i *)&st->wheel[(i-61)&0xff]);
        d = _mm_add_epi32(a,b);
        _mm_storeu_si128((__m128i *)&st->wheel[i], d);
        _mm_storeu_si128((__m128i *)&st->wheel2[i], _mm_xor_si128(c,d));
    }

    for(; i < 64; i++)
    {
        st->wheel[i] = st->wheel[(i-24)] + st->wheel[(i-55)&0xff];
        st->wheel2[i]= st->wheel[i] ^ st->wheel[(i-61)&0xff];
    }

    for(; i < 256; i+=4)
    {
        a = _mm_loadu_si128((__m128i *)&st->wheel[(i-24)]);
        b = _mm_loadu_si128((__m128i *)&st->wheel[(i-55)]);
        c = _mm_loadu_si128((__m128i *)&st->wheel[(i-61)]);
        d = _mm_add_epi32(a,b);
        _mm_storeu_si128((__m128i *)&st->wheel[i], d);
        _mm_storeu_si128((__m128i *)&st->wheel2[i], _mm_xor_si128(c,d));
    }

    st->index=0;
}

#endif

#endif
#endif
