import socket

ADDR = ('localhost', 12000)

with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as server_sock:
    server_sock.bind(ADDR)
    print(f"Mirror Server active on {ADDR[0]}:{ADDR[1]}...")

    while True:
        data, client_addr = server_sock.recvfrom(2048)
        content = data.decode('utf-8')
        print(f"From {client_addr}: {content}")
        result = f"Mirror: '{content[::-1]}' (Len: {len(content)})"
        server_sock.sendto(result.encode('utf-8'), client_addr)