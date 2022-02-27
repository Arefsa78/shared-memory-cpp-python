from multiprocessing import shared_memory
import numpy as np
import mmap
import ctypes
import os

shm_a = shared_memory.SharedMemory(name="MySharedMemory", create=False)
buffer = shm_a.buf

arr = np.frombuffer(buffer.tobytes(), dtype="double")
# lst = arr.tolist()
print(arr)
