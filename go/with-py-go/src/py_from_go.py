import ctypes
import time

so = ctypes.cdll.LoadLibrary('../lib/_go_fib.dll')
# so = ctypes.cdll.LoadLibrary('../lib/_fib.so')


gfib = so.Fib

def pfib(i):
    if i <= 2:
        return 1
    else:
        return pfib(i - 1) + pfib(i - 2)

def main():
    print('go running')
    gstt = time.time()
    gres = gfib(40)
    gust = time.time() - gstt
    '''
    print('go finish, py running')
    pstt = time.time()
    pres = pfib(40)
    pust = time.time() - pstt
    print('py finish')
    '''
    print(f"go use time {gust}s, result {gres}") #; py use time {pust}s, result {pres}.")

if __name__ == '__main__':
    main()
