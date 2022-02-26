from multiprocessing import shared_memory
import numpy as np
import mmap
import ctypes
import os
import array

shm_a = shared_memory.SharedMemory(name="MySharedMemory", create=False)
buffer = shm_a.buf

arr = np.array(array.array('f', buffer.tobytes()))
# lst = arr.tolist()
print(arr)
