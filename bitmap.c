#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BITS_PER_LONG                    64
#define BITOP_MASK(nr)		         (1UL << ((nr) % BITS_PER_LONG))
#define BITOP_WORD(nr)		         ((nr) / BITS_PER_LONG)
#define BITS_PER_BYTE                    8
#define DIV_ROUND_UP(n,d)                (((n) + (d) - 1) / (d))
#define BITS_TO_LONGS(nr)                DIV_ROUND_UP(nr, BITS_PER_BYTE * sizeof(long))
#define BIT_WORD(nr)		         ((nr) / BITS_PER_LONG)
#define BITMAP_FIRST_WORD_MASK(start)    (~0UL << ((start) & (BITS_PER_LONG - 1)))
#define BITMAP_LAST_WORD_MASK(nbits)     (~0UL >> (-(nbits) & (BITS_PER_LONG - 1)))
#define small_const_nbits(nbits)         ((nbits) <= BITS_PER_LONG)

#define DECLARE_BITMAP(name,bits) \
		uint64_t name[BITS_TO_LONGS(bits)]

/**
 * __set_bit - Set a bit in memory
 * @nr: the bit to set
 * @addr: the address to start counting from
 *
 * Unlike set_bit(), this function is non-atomic and may be reordered.
 * If it's called on the same region of memory simultaneously, the effect
 * may be that only one operation succeeds.
 */
static void set_bit(int nr, volatile uint64_t *addr)
{
	uint64_t mask = BITOP_MASK(nr);
	uint64_t *p = ((uint64_t *)addr) + BITOP_WORD(nr);

	*p  |= mask;
}

static void clear_bit(int nr, volatile uint64_t *addr)
{
	uint64_t mask = BITOP_MASK(nr);
	uint64_t *p = ((uint64_t *)addr) + BITOP_WORD(nr);

	*p &= ~mask;
}

/**
 * test_bit - Determine whether a bit is set
 * @nr: bit number to test
 * @addr: Address to start counting from
 */
static int test_bit(int nr, const volatile uint64_t *addr)
{
	return 1UL & (addr[BITOP_WORD(nr)] >> (nr & (BITS_PER_LONG-1)));
}

static inline void bitmap_zero(uint64_t *dst, unsigned int nbits)
{
	if (small_const_nbits(nbits))
		*dst = 0UL;
	else {
		unsigned int len = BITS_TO_LONGS(nbits) * sizeof(uint64_t);
		memset(dst, 0, len);
	}
}

int main()
{
	DECLARE_BITMAP(local_map, 100);
	bitmap_zero(local_map, 100);
	set_bit(0, local_map);
	set_bit(1, local_map);
	set_bit(3, local_map);
	set_bit(99, local_map);
	set_bit(97, local_map);
	int i;
	for (i = 0; i < 100; i++) {
		if (test_bit(i, local_map))
			printf("bit %d is set\n", i);
	}
}
