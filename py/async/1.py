import time
import asyncio

class Lia(list):
    def __getitem__(self, *args):
        return super(Lia, self).__getitem__(*args)
    
class Li(list):
    def __getitem__(self, *args):
        time.sleep(0.2)
        return super(Li, self).__getitem__(*args)

def t1():
    li = Li([1,2,3,4])
    print('start to read four items, delay for 0.2 s for each item')
    t = time.time()
    r = [li[a] for a in range(len(li))]
    ut = time.time() - t
    print('r')
    print('Li use time for', ut, '\bs')

async def r1(li):
    print('start reading', li)
    r = []
    t = time.time()
    for i in range(len(li)):
        r.append(li[i])
        await asyncio.sleep(0.2)
        print('read one', li[i])
    ut = time.time() - t
    print('Lia', li, 'use time for', ut, 's')

def t2():
    async def m():
        li = Lia('abcd')
        l1 = Lia('1234')
        l = (r1(li), r1(l1))
        await asyncio.wait(l)
    loop = asyncio.get_event_loop()
    t = time.time()
    loop.run_until_complete(m())
    ut = time.time() - t
    print('finish in', ut, 's')
    loop.close()

if __name__ == '__main__':
    t1()
    print('\n'*3, 'next t2', '\n'*3)
    t2()
