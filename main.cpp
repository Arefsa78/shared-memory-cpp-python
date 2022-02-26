#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>

#define SHARE_MEM_SIZE 1000

int main() {
   using namespace boost::interprocess;


    struct shm_remove {
        shm_remove() { shared_memory_object::remove("MySharedMemory"); }
        ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
    } remover;

    shared_memory_object shm (create_only, "MySharedMemory", read_write);
    shm.truncate(sizeof(float)*SHARE_MEM_SIZE);
    //Map the whole shared memory in this process
    mapped_region region(shm, read_write);

    //Write all the memory to 1
    std::memset(region.get_address(), 1, region.get_size());

    float* start = (float*)(region.get_address());
    float* end = start + SHARE_MEM_SIZE;    
    int i = 1;



    for (float* p = start; p < end; p++) { 
        *p = (float)i + (float)i/10000;
        i++;
    }

    for (float* p = start; p < end; p++) { 
        std::cout << *p << std::endl;
    }

    std::cout << "Done! now waiting..." << std::endl;
    std::cout << sizeof(float) << std::endl;
    while(1);

}