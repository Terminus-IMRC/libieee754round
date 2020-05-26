
'''
>>> import struct
>>> hexd = lambda _: print(f"{struct.unpack('Q', struct.pack('d', _))[0]:016x}")

>>> hexd(rcp_rn(3))
3fd5555555555555
>>> hexd(rcp_rd(3))
3fd5555555555555
>>> hexd(rcp_ru(3))
3fd5555555555556
>>> hexd(rcp_rz(3))
3fd5555555555555

>>> hexd(rcp_rn(-3))
bfd5555555555555
>>> hexd(rcp_rd(-3))
bfd5555555555556
>>> hexd(rcp_ru(-3))
bfd5555555555555
>>> hexd(rcp_rz(-3))
bfd5555555555555

>>> hexd(rcp_rn(11))
3fb745d1745d1746
>>> hexd(rcp_rd(11))
3fb745d1745d1745
>>> hexd(rcp_ru(11))
3fb745d1745d1746
>>> hexd(rcp_rz(11))
3fb745d1745d1745

>>> nearbyint_rn(0.5)
0.0
>>> nearbyint_rd(0.5)
0.0
>>> nearbyint_ru(0.5)
1.0
>>> nearbyint_rz(0.5)
0.0

>>> nearbyint_rn(-1.5)
-2.0
>>> nearbyint_rd(-1.5)
-2.0
>>> nearbyint_ru(-1.5)
-1.0
>>> nearbyint_rz(-1.5)
-1.0
'''


from ctypes import cdll, c_long, c_longlong, c_float, c_double
from importlib.machinery import EXTENSION_SUFFIXES
from pathlib import Path


stem = Path(__file__).parent.absolute() / 'ieee754round'
for suffix in EXTENSION_SUFFIXES:
    try:
        lib = cdll.LoadLibrary(stem.with_suffix(suffix))
    except OSError:
        continue
    else:
        break
else:
    raise Exception('ieee754round shared library is not found')

del cdll, EXTENSION_SUFFIXES, Path
del stem, suffix


g = globals()


def add_func(op, dtype, *atypes):
    for rnd in ['rn', 'rd', 'ru', 'rz']:
        name = f'{op}_{rnd}'
        g[name] = getattr(lib, name)
        setattr(g[name], 'restype', dtype)
        setattr(g[name], 'argtypes', atypes)


for op in ['add', 'sub', 'mul', 'div']:
    add_func(op, c_double, c_double, c_double)
    add_func(op + 'f', c_float, c_float, c_float)

for op in ['nearbyint', 'rint', 'rcp']:
    add_func(op, c_double, c_double)
    add_func(op + 'f', c_float, c_float)

add_func('lrint', c_long, c_double)
add_func('lrintf', c_long, c_float)
add_func('llrint', c_longlong, c_double)
add_func('llrintf', c_longlong, c_float)

del c_long, c_longlong, c_float, c_double
del lib, g, op
