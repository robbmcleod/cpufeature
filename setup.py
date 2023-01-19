# -*- coding: utf-8 -*-
########################################################################
#
#       cpufeature
#       License: CC0 1.0
#       Author:  Robert A. McLeod - robbmcleod@gmail.com
#       Created: 2017 December 30
#
#       A Python fork of FeatureDetector by Alexander J. Yee 
#       (https://github.com/Mysticial/FeatureDetector)
#
########################################################################

# flake8: noqa

import os

from setuptools import Extension
from setuptools import setup
from glob import glob

# cpufeature version
major_ver = 0
minor_ver = 2
nano_ver = 1

branch = ''

VERSION = "%d.%d.%d%s" % (major_ver, minor_ver, nano_ver, branch)

# Create the version.py file
open('cpufeature/version.py', 'w').write('__version__ = "%s"\n' % VERSION)

# Global variables
CFLAGS = os.environ.get('CFLAGS', '').split()
LFLAGS = os.environ.get('LFLAGS', '').split()

# Sources and headers
sources = [  
    'cpufeature/cpu_x86.c', 'cpufeature/module.c'
]
inc_dirs = ['cpufeature',]
lib_dirs = []
libs = []
def_macros = []

with open('README.md') as fh:
    long_desc = fh.read()


# List classifiers:
# https://pypi.python.org/pypi?%3Aaction=list_classifiers
classifiers = """\
Development Status :: 3 - Alpha
Intended Audience :: Developers
Intended Audience :: Information Technology
License :: CC0 1.0 Universal (CC0 1.0) Public Domain Dedication
Programming Language :: Python
Programming Language :: Python :: 3.8
Programming Language :: Python :: 3.9
Programming Language :: Python :: 3.10
Programming Language :: Python :: 3.11
Topic :: Software Development :: Libraries :: Python Modules
Topic :: System :: Hardware
Operating System :: Microsoft :: Windows
Operating System :: Unix
"""

setup(name = "cpufeature",
      version = VERSION,
      description = 'Python CPU Feature Detection',
      long_description = long_desc,
      long_description_content_type="text/markdown",
      classifiers = [c for c in classifiers.split("\n") if c],
      author = 'Robert A. McLeod',
      author_email = 'robbmcleod@gmail.com',
      maintainer = 'Robert A. McLeod',
      maintainer_email = 'robbmcleod@gmail.com',
      url = 'http://github.com/robbmcleod/cpufeature',
      license = 'https://creativecommons.org/publicdomain/zero/1.0/legalcode',
      platforms = ['any'],
      ext_modules = [
        Extension( "cpufeature.extension",
                   include_dirs=inc_dirs,
                   define_macros=def_macros,
                   sources=sources,
                   library_dirs=lib_dirs,
                   libraries=libs,
                   extra_link_args=LFLAGS,
                   extra_compile_args=CFLAGS ),
        ],
      # tests_require=tests_require,
      packages = ['cpufeature'],

)
