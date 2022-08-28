CC=clang

CWFLAGS=-Wall
CFFLAGS=-D_GLIBCXX_ASSERTIONS -fexceptions -fstack-protector-strong -fPIE -fasynchronous-unwind-tables -ftrivial-auto-var-init=pattern -mspeculative-load-hardening -mcmse -fsanitize=address,undefined,integer -g
COFLAGS=-mtune=native
CLFLAGS=`pkg-config openssl --libs` -lm

CFLAGS=$(CWFLAGS) $(COFLAGS)

passgen: passgen.o words.o
	$(CC) $(CFLAGS) $(CLFLAGS) passgen.o words.o -o passgen

passgen.o: passgen.c
	$(CC) $(CFLAGS) -Os passgen.c -c

words.o: words.txt
	objcopy -O elf64-littleaarch64 -I binary words.txt words.o

clean:
	rm -f passgen
