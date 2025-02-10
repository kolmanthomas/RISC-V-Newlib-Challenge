#include <chrono>
#include <iostream>
#include <string.h>
#include <vector>

#define ONE_MILLION 1000000

extern "C" {

void * memset_custom(void * ptr, int value, size_t num);
void * memset_ex(void * ptr, int value, size_t num);

} // extern "C"

typedef std::chrono::duration<double, std::micro> double_microseconds;

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

    /*
    std::cout << "Time elapsed for memset (glibc) is: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
    std::cout << "Time elapsed for memset_ex (memset from challenge handout) is: " << std::chrono::duration_cast<std::chrono::microseconds>(end_memset_ex - start_memset_ex).count() << std::endl;
    std::cout << "Time elapsed for memset_custom is: " << std::chrono::duration_cast<std::chrono::microseconds>(end_memset_custom - start_memset_custom).count() << std::endl;
    */
    std::cout << std::fixed 
              << std::chrono::duration_cast<double_microseconds>(end - start).count() / (double) ONE_MILLION << ","
              << std::chrono::duration_cast<double_microseconds>(end_memset_ex - start_memset_ex).count() / (double) ONE_MILLION << ","
              << std::chrono::duration_cast<double_microseconds>(end_memset_custom - start_memset_custom).count() / (double) ONE_MILLION;

}

int main(int argc, char* argv[]) 
{
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <buffer_size>" << std::endl;
        return EXIT_FAILURE;
    } 

    long buffer_size = strtol(argv[1], NULL, 10);
    if (!buffer_size) {
        std::cerr << "Invalid buffer size: " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    run_speed_test(buffer_size);
    return EXIT_SUCCESS;
}
