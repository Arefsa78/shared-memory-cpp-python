from atexit import unregister
from multiprocessing import shared_memory
import numpy as np
import sys


if len(sys.argv) != 2:
    print("s (send) or r (recieve)")
elif sys.argv[1] == 's':
    shm_b = shared_memory.SharedMemory(name="MySharedMemory", create=True, size=20*8)
    
    arr = np.ndarray((1,20), "double", shm_b.buf)
    for i in range(20):
        arr[0][i] = i + i/1000
    
    print(arr)
    print("Done! waiting...")
    while True:
        pass
    
elif sys.argv[1] == 'r':
    shm_a = shared_memory.SharedMemory(name="MySharedMemory", create=False)
    # buffer = shm_a.buf

    # arr = np.frombuffer(buffer.tobytes(), dtype="double")
    # lst = arr.tolist()
    # print(arr)
    # np.delete(arr)
    # del arr
    # del buffer
    shm_a.close()
    # del shm_a
    exit()
else:
    print("s (send) or r (recieve)")

