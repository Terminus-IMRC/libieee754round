
from setuptools import setup, Extension


setup(
    name='ieee754round',
    packages=[
        'ieee754round',
    ],
    version='0.0.0',
    description='Floating-point arithmetic with IEEE 754-compliant rounding',
    author='Yukimasa Sugizaki',
    author_email='sugizaki@hpcs.cs.tsukuba.ac.jp',
    ext_modules=[
        Extension('ieee754round.ieee754round',
                  sources=[
                      'ieee754round/ieee754round.cpp'
                  ]),
    ],
    python_requires='~= 3.7',
)
