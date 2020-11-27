import unittest

import cpufeature

class cpufeature_Tests(unittest.TestCase):

    def setUp(self):
        pass

    def test_all(self):
        cpufeature.print_features()

def test(verbosity=2):
    '''
    test(verbosity=2)

    Run ``unittest`` suite for ``cpuinfo`` package.
    '''
    
    print("`cpufeature` tests for version: {}".format(cpufeature.__version__))
    
    theSuite = unittest.TestSuite()

    theSuite.addTest(unittest.makeSuite(cpufeature_Tests))

    return unittest.TextTestRunner(verbosity=verbosity).run(theSuite)


if __name__ == '__main__':
    test()