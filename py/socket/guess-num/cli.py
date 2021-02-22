import socket as sk

ADDR = ('0.0.0.0', 10004)
s = sk.socket(sk.AF_INET, sk.SOCK_STREAM)
s.connect(ADDR)

def i():
    s.send(b'10')
    while 1:
        r = s.recv(1024)
        if r == b'exit':
            return 'exit'
        b = input(r.decode())
        s.send(b.encode())

i()
