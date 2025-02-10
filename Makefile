CC = riscv64-unknown-linux-gnu-gcc
CXX = riscv64-unknown-linux-gnu-g++
CFLAGS = -static -Wall -g
AS = riscv64-unknown-linux-gnu-as

main: memset_custom.o 
	$(CC) $(CFLAGS) main.c memset_custom.o -o $@

speed_test: memset_custom.o memset_ex.o speed_test.cpp
	$(CXX) $(CFLAGS) speed_test.cpp memset_custom.o memset_ex.o -o $@

memset_custom.o: memset_custom.s
	$(AS) memset_custom.s -o $@

memset_ex.o: memset_ex.s
	$(AS) memset_ex.s -o $@

run:
	qemu-riscv64-static main

clean:
	rm -f main speed_test main.o memset_custom.o memset_ex.o 
