# python test
import time
from expalts import expalts

n = 40
print('C++: bones limit')
start_time = time.perf_counter_ns()
print('Answer:', expalts.bones(n,0))
print('Time:', (time.perf_counter_ns() - start_time) / 1e9, 's')

print('C++: bones in-built')
start_time = time.perf_counter_ns()
print('Answer:', expalts.bones(n,1))
print('Time:', (time.perf_counter_ns() - start_time) / 1e9, 's')

print('C++: bones laplace')
start_time = time.perf_counter_ns()
print('Answer:', expalts.bones(n,2))
print('Time:', (time.perf_counter_ns() - start_time) / 1e9, 's')

# View methods in the module
help(expalts)