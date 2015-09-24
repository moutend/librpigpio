clean: *.o
	rm -rf *.o
librpigpio.so: rpigpio.o
	gcc -shared ./rpigpio.o -o ./librpigpio.so
rpigpio.o: rpigpio.c
	gcc -c rpigpio.c
install: librpigpio.so
	cp ./librpigpio.so /usr/lib
	rm -rf *.o
