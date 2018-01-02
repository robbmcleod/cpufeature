
# Generation of 'magic' numbers for bitmasking to extract 
# values from cpuid

def bitmask(mask):
    '''
    First element in `mask` is least-significant bit, last element is most-significant.
    '''
    result = 0
    for index, x in enumerate(mask):
        result |= x << index
    return result


ways = bitmask([0]*22 + [1]*10)
partitions = bitmask([0]*12 + [1]*10)
line_size = bitmask([1]*12)
print( 'Masks for cache values:')
print( 'ways mask: %d'%ways )
print( 'partitions mask: %d'%partitions )
print( 'line_size mask: %d'%line_size )




