'''
encoder = (b'\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f'
        b'\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3a\x3b\x3c\x3d\x3e\x3f'
        b'\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4a\x4b\x4c\x4d\x4e\x4f'
        b'\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5a\x5b\x5c\x5d\x5e\x5f'
        b'\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6a\x6b\x6c\x6d\x6e\x6f'
        b'\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7a\x7b\x7c\x7d\x7e\x7f'
        b'\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f'
        b'\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9a\x9b\x9c\x9d\x9e\x9f').replace(b',', b'\x00')
'''
encoder = tuple((0 if a == 44 else a) for a in range(32, 160))

def b128(bs):
    l = len(bs)
    celln = l // 5 + 1
    tb = tob
    r = tuple(tb(bs[a: a+5]) for a in range(celln))
    return bytes(sum(r, ()))

def tob(bs5):
    b = ''.join(bin(b)[2:].zfill(8) for b in bs5).zfill(42)
    e = encoder
    return tuple(e[int(b[a::6], base=2)] for a in range(6))

'''
b = b'abcdef'
r = b128(b)
print(r)
from timeit import timeit
t = timeit(lambda : b128(b), number=1000)
print('timeit time', t)
'''


def wei(bs):
    i1 = bs[0] >> 1
    i = 0b1
    i2 = ((bs[0] & i) << 6) | (bs[1] >> 2)
    i = (i << 1) + 1
    i2 = ((bs[1] & i) << 5) | (bs[2] >> 3)
