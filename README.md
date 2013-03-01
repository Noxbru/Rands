# RANDS

Rands is a little random number generator library. It's main
purpose is to just generate random numbers using various
generators.

It supports two ways of producing random numbers. One based
on a general state, available from all the program. And other
based on states, so you can have more than one sources of
random numbers. This is interesting if you are doing parallel
computations and need a thread-safe way to produce numbers.

So far, it only has two generators, but this will change with
time (and with the ones I think are more interesting) But
if you want to contribute to the code, just send them (^\_^)

## Generators

This library aims to have some interesting generators. Maybe
they are not interesting for everybody, but as this thing will
grow, surely you can find something.

Here I will write something about the generators that are
implemented. For more information, in their source files
there will be (I hope) more information about how they work.

* Parisi-Rapuano
    * Type: Lagged Fibonacci Generator
    * Period: Unknown (although should be near to (2⁵⁵-1)·32)
* Well
    * Type: Twisted Generalised Feedback Shift Register
    * Period: 2⁵¹²-1

Note: For a little perspective, my biggest simulation has been
the Ising model (which is fairly little although bigger than
most typical uses) And I needed only
`50·8·200000·(8²+16²+24²+32²) = 153.6·10⁹ ≈ 2³⁷` random numbers.

## Usage

This library aims to be as easy as possible to use, so there
will be very few functions for each generator, and they all
will follow the same convention.

For each generator you will have:

* General functions:
    * \*\_srand(seed): This seeds the generator
    * \*\_rand():      This returns a random number
* State functions:
    * \*\_init\_st(state \*\*st):      This initializes a state
    * \*\_clear\_st(state \*st):       This clears the state
    * \*\_srand\_st(state \*st, seed): This seeds the state
    * \*\_rand\_st(state \*st):        This returns a random number

For the general usage of the generators, you only have to
seed them using the `srand` function, and then just
get numbers using the `rand` function.

For the states version, you need to do some previous work, and
there's three ways to prepare and use them.

###### Method 1
1. Create the pointer to the state:          `*_state *st`
2. Use the init function on the state:       `*_init_st(&st)`
3. Seed it!:                                 `*_srand_st(st,seed)`
4. Just get numbers using the rand function: `*_rand_st(st)`
5. When finished, just clear the state:      `*_clear_st(st)`

###### Method 2
It's like the first, but allocating and freeing the state
manually. (In fact, this is what the init and clear functions do
behind stage)

1. Create the pointer to the state:          `*_state *st`
2. Allocate the memory for the state:        `st=malloc(sizeof(*_state))`
3. Seed it!:                                 `*_srand_st(st,seed)`
4. Just get numbers using the rand function: `*_rand_st(st)`
5. When finished, just clear the state:      `free(st)`

###### Method 3
Avoiding the use of the init/clear functions by using
a 'real' state instead of a pointer.

1. Create the state:                         `*_state st`
2. Seed it!:                                 `*_srand_st(&st,seed)`
3. Use it to get numbers:                    `*_rand_st(&st)`

NOTE: Please, be careful with the use of pointers and the `&` operator.
Methods 1 and 2 doesn't need to use `&` when seeding the states or
geting numbers.

## Configuration
This library has a little `rands_config.h` header where you
can choose diferent options for it. Specifically, you can
choose if you want to have all the generators, and if not
which ones to have. And you can also choose whether you
want to be able to use states or not.

## Issues and TODO list
Here I will write down all the things of the library I think
are issues and need to be repaired (hence the name TODO list).
Some of them, I really don't know how to correct them so they
will be here for a looooong time, sorry about that. Although 
I will provide solutions to some of them, you will have to
implement them manually as they are not in the code.

Not in any particular order:

* The function for seeding the generators is currently
  `C rand`. If you want to use other you will have to change
  it in the code, sorry.
* The function for seeding the states *IS NOT* thread-safe.
  
  This can be dealt with in two ways:
  * The first is the obvious: make sure that only one state
    is being seeded at a time.
  * The second is to rewrite the function to seed the states
    so it is thread-safe. This can be done by just embeding
    a 'one-line generator' in the seed function.
* Support for 32 and 64-bits. Currently the library uses
  `unsigned int` as the type for the numbers and the internal
  states, which in my machine is 32-bits long, but changing
  it to `unsigned long int` you should be able to produce
  64-bits long numbers. Maybe I can make some kind of config
  option to choose between them.
* Things that I am sure I have forgotten =)

###### TODO LIST
These are the things that are not issues but still need
to be done.

* Add licenses and that kind of things.
* Write the documentation for the generators.
* Write a little add-up for generating distributions.

###### DONE LIST
Just that, the done list.

* Changelog Started.
* Makefile done. Although you still need to use the
  resulting object as source for your program.
