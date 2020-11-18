#!/bin/bash
# See for the example use of Valgrind as suggest by CPython:
#   https://github.com/python/cpython/blob/master/Misc/README.valgrind
#   https://github.com/python/cpython/blob/master/Misc/valgrind-python.supp
# and the following StackOverflow discussion:
#   http://stackoverflow.com/questions/3982036/how-can-i-use-valgrind-with-python-c-extensions
valgrind --tool=memcheck --leak-check=full -v --suppressions=valgrind-python.supp \
                                          python -c "import cpufeature; cpufeature.print_features()"
