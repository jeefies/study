import socket
from threading import Thread

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('192.168.3.55', 8080))

s.listen(5)
print('waiting for connection')

def tcp(sock, addr):
    print('Accept a new connection from %s:%s' % addr)
    sock.send(b'success')
    while 1:
        data = sock.recv(1024)
        time.sleep(1)
        if not data or data == b'exit':
            break
        sock.send(b'welcome! {}!'.format(data))
    cock.close()

while 1:
    sock, addr = s.accept()
    t = Thread(target=tcp, args=(sock, addr))
    t.start()
