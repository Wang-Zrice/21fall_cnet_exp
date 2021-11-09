all: build/ts build/tc build/us build/uc build/ds build/dc

build/ts: build tcp_server.c net.h
	gcc -o build/ts tcp_server.c

build/tc: build tcp_client.c net.h
	gcc -o build/tc tcp_client.c

build/us: build udp_server.c net.h
	gcc -o build/us udp_server.c

build/uc: build udp_client.c net.h
	gcc -o build/uc udp_client.c

build/ds: build dialog_server.c net.h
	gcc -o build/ds dialog_server.c

build/dc: build dialog_client.c net.h
	gcc -o build/dc dialog_client.c

build:
	mkdir -p build

clean:
	rm -r build

.PHONY: clean
