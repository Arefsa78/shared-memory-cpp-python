#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>

#define SHARE_MEM_SIZE 20
#define DATA_TYPE double

int main(int argc, char** argv) {
    using namespace boost::interprocess;
    std::cout << argv[0] << ", " << argv[1] << std::endl;
    if (argc != 2){
        std::cout << "s (send) or r (recieve)" << std::endl;
    }
    else if (argv[1][0] == 'r'){
        struct shm_remove {
            shm_remove() { shared_memory_object::remove("MySharedMemory"); }
            ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
        } remover;

        std::cout << "Opening" << std::endl;
        shared_memory_object shm (open_only, "MySharedMemory", read_only);
        std::cout << "Opened" << std::endl;
        
        //Map the whole shared memory in this process
        mapped_region region(shm, read_only);

        //Write all the memory to 1

        DATA_TYPE* start = (DATA_TYPE*)(region.get_address());
        DATA_TYPE* end = start + SHARE_MEM_SIZE;    
        int i = 1;

        for (DATA_TYPE* p = start; p < end; p++) { 
            std::cout << *p << std::endl;
        }

        std::cout << "Done!" << std::endl;
    }
    else if (argv[1][0] == 's'){

        shared_memory_object shm (create_only, "MySharedMemory", read_write);
        shm.truncate(sizeof(DATA_TYPE)*SHARE_MEM_SIZE);
        //Map the whole shared memory in this process
        mapped_region region(shm, read_write);

        //Write all the memory to 1
        std::memset(region.get_address(), 1, region.get_size());

        DATA_TYPE* start = (DATA_TYPE*)(region.get_address());
        DATA_TYPE* end = start + SHARE_MEM_SIZE;    
        int i = 1;

        for (DATA_TYPE* p = start; p < end; p++) { 
            *p = (DATA_TYPE)i + (DATA_TYPE)i/10000;
            i++;
        }

        for (DATA_TYPE* p = start; p < end; p++) { 
            std::cout << *p << std::endl;
        }

        std::cout << "Done! now waiting..." << std::endl;
        std::cout << sizeof(DATA_TYPE) << std::endl;
        while(1);
    }
    else {
        std::cout << "s (send) or r (recieve)" << std::endl;
    }

}