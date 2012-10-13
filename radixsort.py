import sys
import timeit
from random import randint

def radix_sort(input):
  output = list(input)
  mask = 0xff;
  for i in range(4):
    count = [0] * 256
    dup = [0] * len(output)
    for j in range(len(output)):
      digit = (output[j] & mask) >> (8 * i)
      count[digit] += 1
    
    offset = 0
    for k in range(256):
      if count[k] == 0:
        continue
      t = count[k]
      count[k] = offset
      offset += t
    
    for j in range(len(input)):
      digit = (output[j] & mask) >> (8 * i)
      dup[count[digit]] = output[j]
      count[digit] += 1
      
    output = list(dup)
    mask <<= 8
  return output

input = []
for i in range(int(sys.argv[1])):
  input.append(randint(0, 0x7fffffff))

stmt0 = 'from __main__ import radix_sort; output = radix_sort(%s)' % input
stmt1 = 'ref = sorted(%s)' % input

t0 = timeit.Timer(stmt = stmt0)
t1 = timeit.Timer(stmt = stmt1)

'''
output = radix_sort(input)
ref = sorted(input)
print "In:", input
print "Out:", output
print ref == output
'''

print 'radixsort: ', t0.timeit(1)
print 'sorted', t1.timeit(1)