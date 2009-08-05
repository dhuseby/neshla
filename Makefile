all:
	gcc data/*.c expressions/*.c output/*.c system/*.c *.c -o _bin/neshla

clean:
	rm _bin/neshla
	rm *.o
	rm data/*.o
	rm expressions/*.o
	rm output/*.o
	rm system/*.o

