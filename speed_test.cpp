#include <chrono>
#include <iostream>
#include <string.h>

extern "C" void * memset_custom(void * ptr, int value, size_t num);
extern "C" void * memset_ex(void * ptr, int value, size_t num);

//const size_t buffer_size = 1024;
//const size_t buffer_size = 65536;
//const size_t buffer_size = 1048576;
const size_t buffer_size_1 = 33554432;

void run_speed_test(size_t buffer_size)
{
    void * ptr_memset = malloc(buffer_size);
    int value = 4;

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();    
    memset(ptr_memset, value, buffer_size); 
    std::chrono::high_resolution_clock::time_point end  = std::chrono::high_resolution_clock::now();    

    void * ptr_memset_ex = malloc(buffer_size);

    std::chrono::high_resolution_clock::time_point start_memset_ex = std::chrono::high_resolution_clock::now();    
    memset_ex(ptr_memset_ex, value, buffer_size); 
    std::chrono::high_resolution_clock::time_point end_memset_ex = std::chrono::high_resolution_clock::now();    

    void * ptr_memset_custom = malloc(buffer_size);

    std::chrono::high_resolution_clock::time_point start_memset_custom = std::chrono::high_resolution_clock::now();    
    memset_custom(ptr_memset_custom, value, buffer_size); 
    std::chrono::high_resolution_clock::time_point end_memset_custom = std::chrono::high_resolution_clock::now();    

    std::cout << "Time elapsed for memset (glibc) is: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
    std::cout << "Time elapsed for memset_ex (memset from challenge handout) is: " << std::chrono::duration_cast<std::chrono::microseconds>(end_memset_ex - start_memset_ex).count() << std::endl;
    std::cout << "Time elapsed for memset_custom is: " << std::chrono::duration_cast<std::chrono::microseconds>(end_memset_custom - start_memset_custom).count() << std::endl;

}

int main(int argc, char* argv[]) 
{
    run_speed_test(buffer_size_1);
    return 0;
}
