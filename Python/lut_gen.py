# generate lookup tables
import numpy as np
import math

x_32 = np.linspace(0.0, 1.0, 32, endpoint=False, dtype=np.float32)
x_64 = np.linspace(0.0, 1.0, 64, endpoint=False, dtype=np.float32)

sinf_32 = np.sin(x_32 * math.tau, dtype=np.float32)
sinf_64 = np.sin(x_64 * math.tau, dtype=np.float64)

np.random.seed(237)
randf_1024 = np.float32(np.random.rand(1024))
randf_pol_1024 = np.float32(np.random.rand(1024) * 2 - 1)

def print_c_f_array(a):
    print('{ ', end='')
    for thing in a[:-1]:
        print(f'{thing}f, ', end='')
    print(f'{a[-1]}f {"}"};')

print_c_f_array(sinf_32)
print()
print_c_f_array(sinf_64)
print()
print_c_f_array(randf_1024)
print()
print_c_f_array(randf_pol_1024)
print()

