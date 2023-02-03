'''
Module ``cpufeature``

@author:  Robert A. McLeod
@email: robbmcleod@gmail.com
'''

from cpufeature.version import __version__
from cpufeature.extension import CPUFeature
from cpufeature.test_cpufeature import test

def print_features():
    print( "=== CPU FEATURES ===" )
    for key, value in CPUFeature.items():
        print( '    {:24}: {}'.format(key, value) )
    


