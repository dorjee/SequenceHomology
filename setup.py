import os
from setuptools import setup, Extension

# allow setup.py to be run from any path
os.chdir(os.path.normpath(os.path.join(os.path.abspath(__file__), os.pardir)))

homology_module = Extension("homology_module", 
                            define_macros = [
                                ('MAJOR_VERSION', '1'),
                                ('MINOR_VERSION', '1')
                            ],
                            sources = ["homology_module.c"])

with open(os.path.join(os.path.dirname(__file__), 'README.md')) as readme:
    README = readme.read()
    
setup(
    name = "homology-module",
    version = "1.1",
    description = 'Python C extension to calculate sequence homology for Conservancy Analysis.',
    author = 'dorjee gyaltsen',
    author_email = 'emaildorjee@gmail.com',
    long_description = README,
    ext_modules = [homology_module],
    classifiers = [
        'Intended Audience :: Developers',
        'Topic :: Scientific/Engineering :: Bio-Informatics',
        'Programming Language :: Python :: 3.9',
    ]
)