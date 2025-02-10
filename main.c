#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void * memset_custom(void * ptr, int value, size_t num);

void test_when_num_is_zero()
{
    size_t num = 0;
    void * ptr = malloc(num);
    int value = 4;

    char * res = memset_custom(ptr, value, num);

    assert(res == ptr);
}

void test_aligned_mem()
{
    size_t num = 200;
    int value = 3;
    char * res = memset_custom(malloc(num), value, num);
    char * c_res = memset(malloc(num), value, num);

    assert(memcmp(res, c_res, num) == 0);
}

void test_unaligned_mem()
{
    size_t num = 200;
    int value = 3;
    /* Malloc always returns suitably aligned memory, so we need to unalign it */
    void * ptr = malloc(num + 1);
    ptr += 1; 
    char * res = memset_custom(ptr, value, num);

    char * c_res = memset(malloc(num), value, num);

    assert(memcmp(res, c_res, num) == 0);
}

int main(int argc, char *argv[])
{
    printf("Starting memset_custom tests\n");
    
    test_when_num_is_zero();
    printf("Test \"test_when_num_is_zero\" passed\n");
    test_aligned_mem();
    printf("Test \"test_aligned_mem\" passed\n");
    test_unaligned_mem();
    printf("Test \"test_unaligned_mem\" passed\n");

    printf("Successfully passed all tests\n");
}
