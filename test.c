#include <stdio.h>

#define PGDIR_SIZE  0x40000000
#define PGDIR_MASK  (~(PGDIR_SIZE-1))

#define pgd_addr_end(addr, end)						\
({	unsigned long __boundary = ((addr) + PGDIR_SIZE) & PGDIR_MASK;	\
	(__boundary - 1 < (end) - 1)? __boundary: (end);		\
})

int main()
{
	int start = 0;
	int len = 0x00001000;

	int end = 0x00001000;
	int next = pgd_addr_end(start, end);
	printf("next %lx\n", next);
}
