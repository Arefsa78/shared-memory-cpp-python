from dataclasses import dataclass
import time
import random

from scipy import rand

N = 100000

data = [random.random() for _ in range(N)]
data_str = [str(d) for d in data]
data_byte = [str(d).encode() for d in data]

start = time.time()
for i in data_str:
    float(i)
end = time.time()

diff_str = end - start

start = time.time()
for i in data_byte:
    float(i)
end = time.time()

diff_byte = end - start

print(diff_str, diff_byte)
