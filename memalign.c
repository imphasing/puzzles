#include <malloc.h>
#include <stdint.h>
#include <stddef.h>


void * memalign(size_t blocksize, size_t bytes)
{
	// allocate an extra pointer to store the original allocated address in,
	// as well as an extra blocksize to find an aligned address in
	size_t allocate_size = sizeof(intptr_t) + blocksize + bytes;

	char *data = malloc(allocate_size);

	// store original malloc address at the start of the data
	intptr_t data_start = (intptr_t) data;

	data += sizeof(intptr_t);
	int offset_size = 0;

	while (((intptr_t) data + offset_size) % blocksize != 0)
	{
		offset_size += 1;
	}

	char *aligned_start = data += offset_size;

	// store original malloc address in the area of size_t before the aligned address
	char *before_aligned = aligned_start - sizeof(intptr_t);
	*(intptr_t *) before_aligned = data_start;

	return aligned_start;
}


void memalign_free(void *data)
{
	// we assume this memory was allocated with memalign, otherwise LOL WHOOPS
	// grab the original malloc'd address in the size_t before the aligned address
	char *original_malloc_start = data - sizeof(intptr_t);
	intptr_t malloc_address = * (intptr_t *) original_malloc_start;

	free((void *) malloc_address);
}


int main(int argc, char **argv)
{
	void *aligned4 = memalign(4, 1024);
	void *aligned8 = memalign(8, 1024);
	void *aligned16 = memalign(16, 1024);
	void *aligned128 = memalign(128, 1024);

	printf("Aligned at 4 bytes? %s\n", (intptr_t) aligned4 % 4 == 0 ? "yes" : "no");
	printf("Aligned at 8 bytes? %s\n", (intptr_t) aligned8 % 8 == 0 ? "yes" : "no");
	printf("Aligned at 16 bytes? %s\n", (intptr_t) aligned16 % 16 == 0 ? "yes" : "no");
	printf("Aligned at 128 bytes? %s\n", (intptr_t) aligned128 % 128 == 0 ? "yes" : "no");

	memalign_free(aligned4);
	memalign_free(aligned8);
	memalign_free(aligned16);
	memalign_free(aligned128);

	return 0;
}


