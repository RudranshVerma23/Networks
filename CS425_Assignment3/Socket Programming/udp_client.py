import socket

SERVER_ADDR = ('localhost', 12000)

with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as client_sock:
    msg = input("Type something to see it in the mirror: ")

    client_sock.sendto(msg.encode('utf-8'), SERVER_ADDR)
    response_data, _ = client_sock.recvfrom(2048)
    print(response_data.decode('utf-8'))