CC=clang

CWFLAGS=-Wall
CFFLAGS=-D_GLIBCXX_ASSERTIONS -fexceptions -fstack-protector-strong -fPIE -fasynchronous-unwind-tables -ftrivial-auto-var-init=pattern -mspeculative-load-hardening -mcmse -fsanitize=address,undefined,integer
COFLAGS=-Os -mtune=native

CFLAGS=$(CWFLAGS) $(CFFLAGS) $(COFLAGS)

passgen: passgen.c
	$(CC) $(CFLAGS) passgen.c -o passgen

clean:
	rm -f passgen
