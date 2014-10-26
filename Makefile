CC=gcc
DEPS = dictcheck.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

cryptkeeper: Vigenere.o
	gcc -o break_vigenere Vigenere.o