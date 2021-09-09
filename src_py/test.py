# python test
import time
from expalts import expalts

n = 40
print('C++: ebits')
start_time = time.perf_counter_ns()
print('Answer:', expalts.ebits(n))
print('Time:', (time.perf_counter_ns() - start_time) / 1e9, 's')

print('C++: byones ebits')
start_time = time.perf_counter_ns()
print('Answer:', expalts.byones(n,0))
print('Time:', (time.perf_counter_ns() - start_time) / 1e9, 's')

print('C++: byones inbuilt')
start_time = time.perf_counter_ns()
print('Answer:', expalts.byones(n,1))
print('Time:', (time.perf_counter_ns() - start_time) / 1e9, 's')

# View methods in the module
help(expalts)