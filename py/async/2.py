import lzma
import time
import asyncio

async def c(sent):
    return lzma.compress(sent)

def oc(sent):
    return lzma.compress(sent)

def main():
    loop = asyncio.get_event_loop()
    s = (b'amjgsdkfj',
            b'akljfhskjbdf',
            b'dfjhkjngd'
            )
    fs = [c(i) for i in s]
    #fs = [loop.create_task(c(i)) for i in s]
    t = time.time()
    r = loop.run_until_complete(asyncio.wait(fs))
    ut = time.time() -t
    #print([i.result() for i in fs], '\nuse time', ut, 's')
    print('\n'* 3)
    print(r)
    print('\n'* 3)
    loop.close()
    
    t = time.time()
    r = [oc(i) for i in s]
    out = time.time() - t
    print(r, '\norg::use time', out, 's')

main()
