import socket
import sys

# Argumentuak egiaztatu
if len(sys.argv) != 2:
    print("Erabilera:")
    print("./tcp_client <port>")
    exit(1)
else:
    port = sys.argv[1];

while True:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    ip = "192.168.4.1"
    adr = (ip, int(port))

    #s.connect(("192.168.4.1",4567));
    s.connect(adr);

    mezua = input("[SEND COMMAND]\n> ")
    if not mezua:
        break
    if mezua == "exit":
        exit()

    mezua += "\r"
    mezua = "GET\r"
    s.send(mezua.encode('utf-8'))
    mezua = ""
    while True:
        buf = s.recv(4)
        mezua += buf.decode('utf-8')
        if mezua.find('\n') != -1:
            break
    print("[SERVER RESPONSE]\n" + mezua)

    s.close()
