# Build the progressbar demo (Linux)

demo: bar.o demo.c bar.h
	gcc -Wall bar.o demo.c -o demo

bar.o: bar.c bar.h
	gcc -Wall -c bar.c

clean:
	rm -f *.o demo
