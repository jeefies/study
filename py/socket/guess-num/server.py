from random import randint
import socket as sk
from threading import Thread as thr

ADDR = ('0.0.0.0', 10004)

s = sk.socket(sk.AF_INET, sk.SOCK_STREAM)

s.bind(ADDR)
try:
    s.close()
    s = sk.socket(sk.AF_INET, sk.SOCK_STREAM)
    s.bind(ADDR)
except:
    pass
s.listen()

def serv(sock, addr):
    print('Connet from %s:%s' % addr)
    mts = sock.recv(1024)
    mts = int(mts)
    print('mts recved')
    def ones(sock):
        sock.send(b'guess a number(1~1000):')
        n = randint(1, 1000)
        e = 0
        while 1:
            a = sock.recv(1024)
            if a == b'exit':
                sock.send(b'exit')
                return 0
            try:a = int(a)
            except: return 0
            if a > n:
                sock.send(b'The number is smaller than your guess.')
            elif a < n:
                sock.send(b'The number is bigger than your guess')
            else:
                sock.send(b'Success, you are right!')
                return 1
    while ones(sock):
        pass


def main():
    try:
        while 1:
            sa = s.accept()
            thr(target=serv, args=sa).start()
    except:
        s.close()

main()
